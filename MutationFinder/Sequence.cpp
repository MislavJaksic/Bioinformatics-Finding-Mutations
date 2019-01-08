#include "Sequence.h"



unsigned int Sequence::max_print{20};
std::map<char, char> Sequence::transformer = {{'A', '1'}, {'T', '2'}, {'G', '3'}, {'C', '0'}};
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
  out << std::endl;

  out << "Index:" << sequence.minimizer_index << std::endl;

  return out;
}



void Sequence::Transform() {
  this->sequence.Transform(this->transformer);
}



void Sequence::ExtractMinimizers(unsigned int kmer_length, unsigned int window_length) {
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

const std::vector<KmerTriple>& Sequence::getMinimizers() {
    return this->minimizers;
}

const String& Sequence::getDescription() {
    return this->description;
}

const CharVector& Sequence::getSequence() {
    return this->sequence;
}
