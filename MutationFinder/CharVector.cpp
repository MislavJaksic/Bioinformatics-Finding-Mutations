#include "CharVector.h"



unsigned int CharVector::max_print = {20};



char& CharVector::operator[](const unsigned int index) {
  return this->resizeable_array[index];
}

const char& CharVector::operator[](const unsigned int index) const {
  return this->resizeable_array[index];
}

std::ostream& operator<< (std::ostream &out, const CharVector &vector) {
  out << "[";
  for (unsigned int i = 0; i < vector.Length(); i++) {
    out << vector[i];
    if (i == vector.Length()) {
      break;
    }
    if (i == CharVector::max_print) {
      const unsigned int difference = vector.Length() - CharVector::max_print;
      out << " and " << difference << " more";
      break;
    }
    out << ",";
  }
  out << "]";

  return out;
}

bool operator== (const CharVector &vector_A, const CharVector &vector_B) {
  unsigned int length_A = vector_A.Length();
  unsigned int length_B = vector_B.Length();

  if (length_A != length_B) {
    return false;
  }

  for (unsigned int i = 0; i < length_A; i++) {
    if (vector_A[i] != vector_B[i]) {
      return false;
    }
  }
  return true;
}

bool operator< (const CharVector &vector_A, const CharVector &vector_B) {
  unsigned int length_A = vector_A.Length();
  unsigned int length_B = vector_B.Length();

  if (length_A < length_B) {
    return true;
  } else if (length_A > length_B) {
    return false;
  }

  for (unsigned int i = 0; i < length_A; i++) {
    if (vector_A[i] < vector_B[i]) {
      return true;
    } else if (vector_A[i] > vector_B[i]) {
      return false;
    }
  }
  return false;
}

std::vector<char>::iterator CharVector::begin() {
  return this->resizeable_array.begin();
}

std::vector<char>::iterator CharVector::end() {
  return this->resizeable_array.end();
}



const std::vector<char>& CharVector::GetVector() const {
  return this->resizeable_array;
}



void CharVector::Append(const char &character) {
  this->resizeable_array.push_back(character);
}

void CharVector::Append(const String &string) {
  for (unsigned int i = 0; i < string.Length(); i++) {
    this->Append(string[i]);
  }
}



void CharVector::Transform(std::map<char, char> map) {
  char character;
  for (unsigned int i = 0; i < this->Length(); i++) {
    character = this->resizeable_array[i];
    if (map.count(character)) {
      this->resizeable_array[i] = map[character];
    }
  }
}

void CharVector::Reverse() {
  std::reverse(this->begin(), this->end());
}



unsigned int CharVector::Length() const {
  return this->resizeable_array.size();
}



bool CharVector::IsEmpty() const {
  if (this->Length() < 1) {
    return true;
  }
  return false;
}

bool CharVector::IsNotEmpty() const {
  if (this->IsEmpty()) {
    return false;
  }
  return true;
}



void CharVector::Shrink() {
  this->resizeable_array.shrink_to_fit();
}

void CharVector::Clear() {
  this->resizeable_array.clear();
}

const std::vector<char>& CharVector::GetVector() const {
  return this->resizeable_array;
}

void CharVector::Reverse() {
  std::reverse(this->begin(), this->end());
}

bool CharVector::IsEmpty() const {
  if (this->Length() < 1) {
    return true;
  }
  return false;
}

bool CharVector::IsNotEmpty() const {
  if (this->IsEmpty()) {
    return false;
  }
  return true;
}
