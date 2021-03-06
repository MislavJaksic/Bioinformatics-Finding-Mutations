/*
Author: Josip Kasap
*/

#include "SequenceMapper.h"

std::map<char, char> SequenceMapper::reverse_nucleobase = {{'0', 'C'}, {'1', 'A'}, {'2', 'T'}, {'3', 'G'}};
std::map<char, char> SequenceMapper::reverse_transformation = {{'0', '3'}, {'1', '2'}, {'2', '1'}, {'3', '0'}};
int SequenceMapper::indel = 5;
int SequenceMapper::missmatch_1 = 1;
int SequenceMapper::missmatch_2 = 5;

static std::map<std::tuple<char, char>, int> initPam() {
  std::map<std::tuple<char, char>, int> pam_matrix = {};
  for (char c1 = '0'; c1 <= '3'; c1++) {
    for (char c2 = '0'; c2 <= '3'; c2++) {
      std::tuple<char, char> pamTouple = std::make_tuple(c1, c2);
      if (c1 == c2) {
        pam_matrix.insert(std::pair<std::tuple<char, char>, int>(pamTouple, 0));
      } else if (abs(c1 - c2) == 2) {
        pam_matrix.insert(std::pair<std::tuple<char, char>, int>(pamTouple, SequenceMapper::missmatch_1));
      } else {
        pam_matrix.insert(std::pair<std::tuple<char, char>, int>(pamTouple, SequenceMapper::missmatch_2));
      }
    }
  }
  return pam_matrix;
}

std::map<std::tuple<char, char>, int> SequenceMapper::pam = initPam();

bool operator==(const mutation& mut1, const mutation& mut2) {
  return mut1.mutation_character == mut2.mutation_character && mut1.position == mut2.position && mut1.nucleobase == mut2.nucleobase;
}

std::vector<unsigned int> SequenceMapper::getMatchingPositions(Sequence &sequence_A, Sequence &sequence_B) {
  std::vector<unsigned int> positions{};

  for (const KmerTriple& kmer_triple : sequence_B.minimizers) {
    int k = kmer_triple.GetKmer().Length();
    bool is_on_reverse_helix = kmer_triple.GetKey().GetIsReverse();
    unsigned int position_B = kmer_triple.GetPosition();

    KmerKey key_true{kmer_triple.GetKey().GetKmer(), false};
    KmerKey key_reverse{kmer_triple.GetKey().GetKmer(), true};
    std::vector<unsigned int> positions_true = sequence_A.minimizer_index[key_true];
    std::vector<unsigned int> positions_reverse = sequence_A.minimizer_index[key_reverse];
    bool is_found_true = positions_true.size() >= 1;
    bool is_found_reverse = positions_reverse.size() >= 1;

    bool reverse_helix = !(is_found_reverse == is_on_reverse_helix);
    int reverse_hel = reverse_helix == true ? 1 : 0;

    if (is_found_true) {
      for (auto& position_A : positions_true) {
        int true_position = position_A;
        for (int i = 1; i <= 5; i++) {
          int pos_A_check = position_A - i;
          int pos_B_check = position_B - i;
          if (pos_A_check < 0 || pos_B_check < 0)
            continue;

          if (sequence_A.GetSequence()[pos_A_check] != sequence_B.GetSequence()[pos_B_check]) {
            true_position = -1;
            break;
          }

          pos_A_check = position_A + k + i;
          pos_B_check = position_B + k + i;
          if (pos_A_check >= (int)sequence_A.Length() || pos_B_check >= (int)sequence_B.Length())
            continue;

          if (sequence_A.GetSequence()[pos_A_check] != sequence_B.GetSequence()[pos_B_check]) {
            true_position = -1;
            break;
          }
        }

        if (true_position > -1) {
          positions.push_back(position_A);
          positions.push_back(position_B);
          positions.push_back(reverse_hel);
          positions.push_back(k);
          return positions;
        }
      }
    }
    if (is_found_reverse) {
      for (auto& position_A : positions_true) {
        int true_position = position_A;
        for (int i = 1; i <= 5; i++) {
          int pos_A_check = position_A - i;
          int pos_B_check = position_B - i;
          if (pos_A_check < 0 || pos_B_check < 0)
            continue;

          if (reverse_nucleobase[sequence_A.GetSequence()[pos_A_check]] != sequence_B.GetSequence()[pos_B_check]) {
            true_position = -1;
            break;
          }

          pos_A_check = position_A + k + i;
          pos_B_check = position_B + k + i;
          if (pos_A_check >= (int)sequence_A.GetSequence().Length() || pos_B_check >= (int)sequence_B.GetSequence().Length())
            continue;

          if (reverse_nucleobase[sequence_A.GetSequence()[pos_A_check]] != sequence_B.GetSequence()[pos_B_check]) {
            true_position = -1;
            break;
          }
        }

        if (true_position > -1) {
          positions.push_back(position_A);
          positions.push_back(position_B);
          positions.push_back(reverse_hel);
          positions.push_back(k);
          return positions;
        }
      }
    }
  }



  return positions;
}

std::vector<point> SequenceMapper::getAllMatchingPositions(Sequence &sequence_A, Sequence &sequence_B) {
  std::vector<point> points{};

  bool added_k_and_reverse = false;
  int pos_a = -1000, pos_b = -1000;
  bool reverse_helix = false;

  for (const KmerTriple& kmer_triple : sequence_B.minimizers) {
    unsigned int k = kmer_triple.GetKey().GetKmer().Length();
    bool is_on_reverse_helix = kmer_triple.GetKey().GetIsReverse();
    unsigned int position_B = kmer_triple.GetPosition();

    KmerKey key_true{kmer_triple.GetKey().GetKmer(), false};
    KmerKey key_reverse{kmer_triple.GetKey().GetKmer(), true};
    std::vector<unsigned int> positions_true = sequence_A.minimizer_index[key_true];
    std::vector<unsigned int> positions_reverse = sequence_A.minimizer_index[key_reverse];
    bool is_found_true = positions_true.size() >= 1;
    bool is_found_reverse = positions_reverse.size() >= 1;

    if ((is_found_true || is_found_reverse) && added_k_and_reverse == false) {
      reverse_helix = !(is_found_reverse == is_on_reverse_helix);
      unsigned int reverse_hel = reverse_helix == true ? 1 : 0;
      added_k_and_reverse = true;
      point p{k, reverse_hel};
      points.push_back(p);
    }

    if (is_found_true || is_found_reverse) {
      for (auto& position_A : positions_true) {
        int true_position = position_A;

        if (pos_a >= (int)position_A || -pos_a + (int)position_A <  100) {
          continue;
        } else {
          pos_a = (int)position_A;
        }
        if (pos_b >= (int)position_B || -pos_b + (int)position_B <  100) {
          continue;
        } else {
          pos_b = (int)position_B;
        }

        for (int i = 1; i <= 5; i++) {
          int pos_A_check = position_A - i;
          int pos_B_check = position_B - i;
          if (pos_A_check < 0 || pos_B_check < 0)
            continue;

          if (reverse_helix) {
            if (sequence_A.GetSequence()[pos_A_check] != SequenceMapper::reverse_transformation[sequence_B.GetSequence()[pos_B_check]]) {
              true_position = -1;
              break;
            }
          } else {
            if (sequence_A.GetSequence()[pos_A_check] != sequence_B.GetSequence()[pos_B_check]) {
              true_position = -1;
              break;
            }
          }

          pos_A_check = position_A + k + i;
          pos_B_check = position_B + k + i;
          if (pos_A_check >= (int)sequence_A.GetSequence().Length() || pos_B_check >= (int)sequence_B.GetSequence().Length())
            continue;

          if (reverse_helix) {
            if (sequence_A.GetSequence()[pos_A_check] != SequenceMapper::reverse_transformation[sequence_B.GetSequence()[pos_B_check]]) {
              true_position = -1;
              break;
            }
          } else {
            if (sequence_A.GetSequence()[pos_A_check] != sequence_B.GetSequence()[pos_B_check]) {
              true_position = -1;
              break;
            }
          }
        }

        if (true_position > -1) {
          point p{position_A, position_B};
          points.push_back(p);
        }
      }
    }
  }

  return points;
}

cell get_cell(int cost, int i, int j) {
  cell c;
  c.cost = cost;
  c.parrent_x = i;
  c.parrent_y = j;
  return c;
}

std::list<mutation> SequenceMapper::getGlobalMutations(Sequence &sequence_A, Sequence &sequence_B,
    int position_A, int N, int position_B, int M, bool reverse_helix, int flag) {
  std::list<mutation> mutations{};

  std::map<std::tuple<int, int>, cell> m;

  cell c_init = {0, -1, -1};

  std::tuple<int, int> m_position_init = std::make_tuple(0, 0);
  m.insert(std::pair<std::tuple<int, int>, cell>(m_position_init, c_init));

  for (int j = 1; j <= M; j++) {
    std::tuple<int, int> m_position_1 = std::make_tuple(0, j);
    cell c1 = {j * SequenceMapper::indel, 0, j - 1};
    m.insert(std::pair<std::tuple<int, int>, cell>(m_position_1, c1));
  }
  for (int i = 1; i <= N; i++) {
    std::tuple<int, int> m_position_1 = std::make_tuple(i, 0);
    int zero_flag = 1;//(flag == 0) ? 0 : 1;
    cell c1 = {i * SequenceMapper::indel * zero_flag, i - 1, 0};
    m.insert(std::pair<std::tuple<int, int>, cell>(m_position_1, c1));
  }

  int opt;
  std::tuple<int, int> *best_parrent;
  const CharVector &x = sequence_B.GetSequence();
  const CharVector &y = sequence_A.GetSequence();
  bool goal_cell_end_relaxation = (flag != 1);
  cell *goal_cell = nullptr;
  int goal_cost = 1000000;
  int goal_x{0}, goal_y{0};
  int kN = (int)(0.1 * N);
  if (N > 3000) {
    kN = (int)(0.03 * N);
  }

  for (int i = 1; i <= N; i++) {
    for (int j = std::max(1, i - kN); j <= std::min(M, i + kN); j++) {

      std::tuple<int, int> m_position_match = std::make_tuple(i - 1, j - 1);
      std::tuple<int, int> m_position_insert = std::make_tuple(i, j - 1);
      std::tuple<int, int> m_position_delete = std::make_tuple(i - 1, j);

      if (flag != 0) {
        if (reverse_helix) {
          opt = m[m_position_match].cost + SequenceMapper::pam[
                  std::make_tuple(SequenceMapper::reverse_transformation[x[position_B + j - 1]], y[position_A + i - 1])];
        } else {
          opt = m[m_position_match].cost + SequenceMapper::pam[std::make_tuple(x[position_B + j - 1], y[position_A + i - 1])];
        }
      } else {
        if (reverse_helix) {
          opt = m[m_position_match].cost + SequenceMapper::pam[
                  std::make_tuple(SequenceMapper::reverse_transformation[x[position_B - (j - 1)]], y[position_A - (i - 1)])];
        } else {
          opt = m[m_position_match].cost + SequenceMapper::pam[std::make_tuple(x[position_B - (j - 1)], y[position_A - (i - 1)])];
        }
      }

      best_parrent = &m_position_match;

      if (j > i - kN) {
        int test1 = m[m_position_insert].cost + SequenceMapper::indel;
        if (test1 < opt) {
          opt = test1;
          best_parrent = &m_position_insert;
        }
      }

      if (j < i + kN) {
        int test2 = m[m_position_delete].cost + SequenceMapper::indel;
        if (test2 < opt) {
          opt = test2;
          best_parrent = &m_position_delete;
        }
      }

      cell c = {opt, std::get<0>(*best_parrent), std::get<1>(*best_parrent)};

      m.insert(std::pair<std::tuple<int, int>, cell>(std::make_tuple(i, j), c));

      if (j == M && goal_cell_end_relaxation) {
        if (i == 1) {
          goal_cost = c.cost;
          goal_x = i;
          goal_y = j;
        } else if (c.cost < goal_cost) {
          goal_cost = c.cost;
          goal_x = i;
          goal_y = j;
        }

      }
    }
  }

  int i = N, j = M;
  if (goal_cell_end_relaxation == false) {
    goal_cell = &m[std::make_tuple(i, j)];
  } else {
    goal_cell = &m[std::make_tuple(goal_x, goal_y)];
  }
  cell *current_cell = goal_cell;
  cell *parrent_cell = nullptr;

  while (i > -1 && j > -1) {
    parrent_cell = &m[std::make_tuple(current_cell->parrent_x, current_cell->parrent_y)];

    if (parrent_cell->cost == current_cell->cost) {
      i = current_cell->parrent_x;
      j = current_cell->parrent_y;
      current_cell = parrent_cell;
      continue;
    }

    unsigned int pos_a = (unsigned int)(position_A + i - 1);
    int pos_b = (int)position_B + j - 1;

    if (flag == 0) {
      pos_b = (int)position_B - (j - 1);
      pos_a = (unsigned int)(position_A - (i - 1));
    }

    if (i - current_cell->parrent_x == 1 && j - current_cell->parrent_y == 1) {
      if (reverse_helix) {
        mutation mutt{'X', pos_a, reverse_nucleobase[SequenceMapper::reverse_transformation[x[pos_b]]]};
        if (flag != 0)
          mutations.push_front(mutt);
        else
          mutations.push_back(mutt);
      } else {
        mutation mutt{'X', pos_a, reverse_nucleobase[x[pos_b]]};
        if (flag != 0)
          mutations.push_front(mutt);
        else
          mutations.push_back(mutt);
      }
    } else if (i - current_cell->parrent_x == 1 && j - current_cell->parrent_y == 0) {
      mutation mutt{'D', pos_a, '-'};
      mutations.push_front(mutt);
    } else if (i - current_cell->parrent_x == 0 && j - current_cell->parrent_y == 1) {
      if (reverse_helix) {
        mutation mutt{'I', pos_a + 1, reverse_nucleobase[SequenceMapper::reverse_transformation[x[pos_b]]]};
        if (flag != 0)
          mutations.push_front(mutt);
        else
          mutations.push_back(mutt);
      } else {
        mutation mutt{'I', pos_a + 1, reverse_nucleobase[x[pos_b]]};
        if (flag != 0)
          mutations.push_front(mutt);
        else
          mutations.push_back(mutt);
      }
    }

    i = current_cell->parrent_x;
    j = current_cell->parrent_y;
    current_cell = parrent_cell;
  }

  m.clear();

  return mutations;
}

std::list<mutation> SequenceMapper::getMutations(Sequence &sequence_A, Sequence &sequence_B) {

  std::vector<point> points = this->getAllMatchingPositions(sequence_A, sequence_B);
  if (points.size() < 2) {
    std::list<mutation> mutts{};
    return mutts;
  }

  int k = points[0].x;
  bool reverse_helix = (points[0].y == 1);


  int position_A = points[1].x;
  int position_B = points[1].y;
  int M = position_B + 1;
  int N = (int)(1.2 * M);
  if (position_A - N < 0) {
    N = position_A + 1;
  }


  std::list<mutation> mutations = getGlobalMutations(sequence_A, sequence_B,
                                  position_A, N, position_B, M, reverse_helix, 0);

  for (int i = 1; i < (int)points.size() - 1; i++) {
    position_A = points[i].x + k - 1;
    position_B = points[i].y + k - 1;
    N = points[i + 1].x - position_A + 1;
    M = points[i + 1].y - position_B + 1;
    std::list<mutation> mutations_for_fragment = getGlobalMutations(sequence_A, sequence_B,
        position_A, N, position_B, M, reverse_helix, 1);

    for (auto& mut : mutations_for_fragment) {
      mutations.push_back(mut);
    }
  }

  position_A = points[(int)points.size() - 1].x + k - 1;
  position_B = points[(int)points.size() - 1].y + k - 1;
  M = sequence_B.GetSequence().Length() - position_B;
  N = (int)(1.2 * M);
  if (position_A + (unsigned int)N > sequence_A.GetSequence().Length()) {
    N = sequence_A.GetSequence().Length() - position_A;
  }
  std::list<mutation> mutations_for_fragment = getGlobalMutations(sequence_A, sequence_B,
      position_A, N, position_B, M, reverse_helix, 2);

  for (auto& mut : mutations_for_fragment) {
    mutations.push_back(mut);
  }

  return mutations;
}
