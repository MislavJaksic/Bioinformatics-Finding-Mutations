/*
Author: Mislav Jaksic
*/

#include "Sequence.h"



unsigned int Sequence::max_print{20};
std::map<char, char> Sequence::reverse_nucleobase = {{'0', '3'}, {'1', '2'}, {'2', '1'}, {'3', '0'}};



std::ostream& operator<< (std::ostream &out, const Sequence &sequence) {
  out << "Description:" << sequence.description << std::endl;

  out << "Sequence:" << sequence.sequence << std::endl;

  out << "Minimizers:";
  out << "[";
  for (unsigned int i = 0; i < sequence.minimizers.size(); i++) {
    out << sequence.minimizers[i];
    if (i == sequence.minimizers.size()) {
      break;
    }
    if (i == Sequence::max_print) {
      const unsigned int difference = sequence.minimizers.size() - Sequence::max_print;
      out << " and " << difference << " more";
      break;
    }
    out << ",";
  }
  out << "]";
  out << std::endl;

  out << "Index:" << sequence.minimizer_index << std::endl;

  return out;
}



String& Sequence::GetDescription() {
  return this->description;
}

const String& Sequence::GetDescription() const {
  return this->description;
}

CharVector& Sequence::GetSequence() {
  return this->sequence;
}

const CharVector& Sequence::GetSequence() const {
  return this->sequence;
}



void Sequence::Transform(std::map<char, char> char_pairs) {
  this->sequence.Transform(char_pairs);
}

void Sequence::Reverse() {
  this->sequence.Reverse();
}



void Sequence::ExtractMinimizers(unsigned int kmer_length, unsigned int window_length) {
  this->ClearMinimizers();
  unsigned int window_position = 0;
  unsigned int max_window = this->sequence.Length() - window_length + 1;

  unsigned int true_minimizer_position = 0;
  unsigned int reverse_minimizer_position = 0;

  while (window_position < max_window) {
    true_minimizer_position = this->FindMinimizerOnHelix(kmer_length, window_position, window_length, false);
    reverse_minimizer_position = this->FindMinimizerOnHelix(kmer_length, window_position, window_length, true);

    if (this->IsTrueBiggerThenReverseOfLength(true_minimizer_position, reverse_minimizer_position, kmer_length)) {
      this->AppendMinimizer(reverse_minimizer_position, kmer_length, true);
      window_position = window_position + (reverse_minimizer_position - window_position) + 1;
    } else {
      this->AppendMinimizer(true_minimizer_position, kmer_length, false);
      window_position = window_position + (true_minimizer_position - window_position) + 1;
    }
  }

  this->Shrink();
}

void Sequence::IndexMinimizers(unsigned int kmer_length, unsigned int window_length) {
  this->ClearIndex();
  this->ExtractMinimizers(kmer_length, window_length);

  KmerTriple triple;
  for (unsigned int i = 0; i < minimizers.size(); i++) {
    triple = minimizers[i];
    this->minimizer_index.Add(triple.GetKey(), triple.GetPosition());
  }

  this->ClearMinimizers();
  this->Shrink();
}

unsigned int Sequence::FindMinimizerOnHelix(unsigned int kmer_length, unsigned int window_position, unsigned int window_length, bool is_reverse_helix) {
  unsigned int max_within_window = window_length - kmer_length + 1;

  unsigned int candidate_position = window_position;

  for (unsigned int i = 0; i < max_within_window; i++) {
    if (this->IsOneBiggerThenTwo(candidate_position, window_position + i, kmer_length, is_reverse_helix)) {
      candidate_position = window_position + i;
    }
  }

  return candidate_position;
}

bool Sequence::IsOneBiggerThenTwo(unsigned int one, unsigned int two, unsigned int length, bool is_reverse) {
  char char_one;
  char char_two;
  for (unsigned int i = 0; i < length; i++) {
    char_one = this->sequence[one + i];
    char_two = this->sequence[two + i];

    if (is_reverse) {
      char_one = reverse_nucleobase[char_one];
      char_two = reverse_nucleobase[char_two];
    }

    if (char_one > char_two) {
      return true;
    } else if (char_one < char_two) {
      return false;
    }
  }
  return false;
}

bool Sequence::IsTrueBiggerThenReverseOfLength(unsigned int true_position, unsigned int reverse_position, unsigned int length) {
  char char_one;
  char char_two;
  for (unsigned int i = 0; i < length; i++) {
    char_one = this->sequence[true_position + i];
    char_two = reverse_nucleobase[this->sequence[reverse_position + i]];

    if (char_one > char_two) {
      return true;
    } else if (char_one < char_two) {
      return false;
    }
  }
  return false;
}

void Sequence::AppendMinimizer(unsigned int position, unsigned int length, bool is_reverse) {
  Kmer kmer;
  char character;
  if (is_reverse) {
    for (unsigned int i = 0; i < length; i++) {
      character = reverse_nucleobase[this->sequence[position + i]];
      kmer.Append(character);
    }
  } else {
    for (unsigned int i = 0; i < length; i++) {
      character = this->sequence[position + i];
      kmer.Append(character);
    }
  }
  KmerKey key{kmer, is_reverse};

  KmerTriple triple{key, position};

  minimizers.push_back(triple);
}

void Sequence::SortMinimizers() {
  std::sort(this->minimizers.begin(), this->minimizers.end());
}



bool Sequence::IsReverseAlignment(const Sequence& read) {
  unsigned int alignment_threshold{2};

  unsigned int count_against_complement_votes{this->CountMinimizersAgainstComplement(read)};
  unsigned int count_for_complement_votes{this->CountMinimizersForComplement(read)};

  if (alignment_threshold > (count_against_complement_votes + count_for_complement_votes)) {
    return true;
  }
  return false;
}

void Sequence::CompareWithSequence(const Sequence& read) {
  unsigned int minimizer_print_count{0};
  unsigned int max_minimizer_print{this->max_print / 20};
  unsigned int quorum{this->max_print / 2};

  unsigned int count_against_complement_votes{this->CountMinimizersAgainstComplement(read)};
  unsigned int count_for_complement_votes{this->CountMinimizersForComplement(read)};

  std::cout << read.GetDescription() << std::endl;
  for (auto& read_minimizer : read.minimizers) {
    unsigned int read_minimizer_position{read_minimizer.GetPosition()};
    bool is_read_minimizer_on_reverse{read_minimizer.GetKey().GetIsReverse()};

    bool is_not_reverse_in_index{false};
    bool is_reverse_in_index{true};

    KmerKey true_key{read_minimizer.GetKmer(), is_not_reverse_in_index};
    KmerKey reverse_key{read_minimizer.GetKmer(), is_reverse_in_index};

    std::vector<unsigned int> true_positions{this->minimizer_index[true_key]};
    std::vector<unsigned int> reverse_positions{this->minimizer_index[reverse_key]};

    if (true_positions.size() > 0) {
      bool is_read_reverse{is_read_minimizer_on_reverse == is_reverse_in_index};
      if (minimizer_print_count < max_minimizer_print) {
        std::cout << "Key: " << true_key << std::endl;
        std::cout << "Complement read? " << is_read_reverse << std::endl;

        for (auto& reference_position : true_positions) {
          std::cout << "Refe: ";
          this->PrintPositionSurrounding(reference_position);
          std::cout << "Read: ";
          read.PrintPositionSurrounding(read_minimizer_position);
        }
        std::cout << std::endl;
        minimizer_print_count++;
      }
    }
    if (reverse_positions.size() > 0) {
      bool is_read_reverse{is_read_minimizer_on_reverse == is_not_reverse_in_index};
      if (minimizer_print_count < max_minimizer_print) {
        std::cout << "Key: " << reverse_key << std::endl;
        std::cout << "Complement read: " << is_read_reverse << std::endl;

        for (auto& reference_position : reverse_positions) {
          std::cout << "Refe: ";
          this->PrintPositionSurrounding(reference_position);
          std::cout << "Read: ";
          read.PrintPositionSurrounding(read_minimizer_position);
        }
        std::cout << std::endl;
        minimizer_print_count++;
      }
    }
  }

  if (quorum > (count_against_complement_votes + count_for_complement_votes)) {
    std::cout << "Warning! Did not meet quorum! Reverse the sequence, reduce kmer length or reduce window size." << std::endl;
  }
  std::cout << "Against complementing: " << count_against_complement_votes << std::endl;
  std::cout << "For complementing: " << count_for_complement_votes << std::endl;
}



unsigned int Sequence::CountMinimizersForComplement(const Sequence& read) {
  unsigned int count_for_complement_votes{0};

  for (auto& read_minimizer : read.minimizers) {
    bool is_read_minimizer_on_reverse{read_minimizer.GetKey().GetIsReverse()};

    bool is_not_reverse_in_index{false};
    bool is_reverse_in_index{true};

    KmerKey true_key{read_minimizer.GetKmer(), is_not_reverse_in_index};
    KmerKey reverse_key{read_minimizer.GetKmer(), is_reverse_in_index};

    std::vector<unsigned int> true_positions{this->minimizer_index[true_key]};
    std::vector<unsigned int> reverse_positions{this->minimizer_index[reverse_key]};

    if (true_positions.size() > 0) {
      bool is_read_reverse{is_read_minimizer_on_reverse == is_reverse_in_index};
      if (is_read_reverse == 1) {
        count_for_complement_votes++;
      }
    }
    if (reverse_positions.size() > 0) {
      bool is_read_reverse{is_read_minimizer_on_reverse == is_not_reverse_in_index};
      if (is_read_reverse == 1) {
        count_for_complement_votes++;
      }
    }
  }

  return count_for_complement_votes;
}

unsigned int Sequence::CountMinimizersAgainstComplement(const Sequence& read) {
  unsigned int count_against_complement_votes{0};

  for (auto& read_minimizer : read.minimizers) {
    bool is_read_minimizer_on_reverse{read_minimizer.GetKey().GetIsReverse()};

    bool is_not_reverse_in_index{false};
    bool is_reverse_in_index{true};

    KmerKey true_key{read_minimizer.GetKmer(), is_not_reverse_in_index};
    KmerKey reverse_key{read_minimizer.GetKmer(), is_reverse_in_index};

    std::vector<unsigned int> true_positions{this->minimizer_index[true_key]};
    std::vector<unsigned int> reverse_positions{this->minimizer_index[reverse_key]};

    if (true_positions.size() > 0) {
      bool is_read_reverse{is_read_minimizer_on_reverse == is_reverse_in_index};
      if (is_read_reverse == 0) {
        count_against_complement_votes++;
      }
    }
    if (reverse_positions.size() > 0) {
      bool is_read_reverse{is_read_minimizer_on_reverse == is_not_reverse_in_index};
      if (is_read_reverse == 0) {
        count_against_complement_votes++;
      }
    }
  }

  return count_against_complement_votes;
}



void Sequence::PrintPositionSurrounding(const unsigned int& position) const {
  this->PrintFromTo(position - this->max_print, position);
  std::cout << this->sequence[position] << " ";
  this->PrintFromTo(position + 1, position + this->max_print);
  std::cout << std::endl;
}

void Sequence::PrintFromTo(const unsigned int& from, const unsigned int& to) const {
  unsigned int begin{from};
  unsigned int end;
  if (to > this->Length()) {
    end = this->Length();
  } else {
    end = to;
  }
  unsigned int count{1};
  for (unsigned int i = begin; i < end; i++) {
    std::cout << this->sequence[i];
    if (count % 5 == 0) {
      std::cout << " ";
    }
    count++;
  }
}



unsigned int Sequence::Length() const {
  return this->sequence.Length();
}



void Sequence::Shrink() {
  this->description.Shrink();
  this->sequence.Shrink();
  this->minimizers.shrink_to_fit();
  this->minimizer_index.Shrink();
}

void Sequence::ClearMinimizers() {
  this->minimizers.clear();
}

void Sequence::ClearIndex() {
  this->minimizer_index.Clear();
}

void Sequence::Clear() {
  this->description.Clear();
  this->sequence.Clear();
  this->minimizers.clear();
  this->minimizer_index.Clear();
}
