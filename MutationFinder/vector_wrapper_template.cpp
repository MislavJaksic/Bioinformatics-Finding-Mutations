#include "vector_wrapper_template.h"

bool operator< (VectorWrapper &vector_A, VectorWrapper &vector_B) {
  unsigned int length_A = vector_A.Length();
  unsigned int length_B = vector_B.Length();

  if (length_A < length_B) {
    return true;
  } else if (length_A > length_B) {
    return false;
  }

  for (unsigned int i = 0; i < length_A; i++) {
    if (vector_A[i] > vector_B[i]) {
      return false;
    } else if (vector_A[i] < vector_B[i]) {
      return true;
    }
  }
  return true;
}
