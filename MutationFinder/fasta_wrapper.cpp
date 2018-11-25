#include "fasta_wrapper.h"

FastaWrapper::FastaWrapper(CharVector &description, CharVector &sequence) :
  description(description),
  sequence(sequence) {
}

void FastaWrapper::AppendDescription(String & string) {
  for (unsigned int i = 0; i < Length(string); i++) {
    char character = string[i];
    description.push_back(character);
  }
}

void FastaWrapper::AppendSequence(String &string) {
  for (unsigned int i = 0; i < Length(string); i++) {
    char character = string[i];
    sequence.push_back(character);
  }
}



std::map<char, int> FastaWrapper::CountOccurrences() {
  std::map<char, int> occurrences;

  for (unsigned int i = 0; i < Length(sequence); i++) {
    char character = sequence[i];
    if (IsKeyExists(character, occurrences)) {
      int count_plus_one = GetValueForKey(character, occurrences) + 1;
      UpsertKeyValue(character, count_plus_one, occurrences);
    } else {
      int one = 1;
      UpsertKeyValue(character, one, occurrences);
    }
  }

  return occurrences;
}



void FastaWrapper::Print() {
  std::cout << "FastaWrapper:" << std::endl;
  std::cout << "Description:";

  for (auto& element : description) {
    std::cout << element;
  }

  std::cout << std::endl;
  std::cout << "Sequence:";

  unsigned int len = Length(sequence);
  unsigned int ten = 10;
  unsigned int up_to_ten = std::min(ten, len);
  for (unsigned int i = 0; i < up_to_ten; i++) {
    std::cout << sequence[i];
  }

  std::cout << "..." << std::endl;
}
