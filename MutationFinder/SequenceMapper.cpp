#include "SequenceMapper.h"

std::map<char, char> SequenceMapper::reverse_nucleobase = {{'0', 'C'}, {'1', 'A'}, {'2', 'T'}, {'3', 'G'}};
std::map<char, char> SequenceMapper::reverse_transformation = {{'0', '3'}, {'1', '2'}, {'2', '1'}, {'3', '0'}};
int SequenceMapper::indel = 5;
int SequenceMapper::missmatch_1 = 1;
int SequenceMapper::missmatch_2 = 5;

static std::map<std::tuple<char, char>, int> initPam() {
    std::map<std::tuple<char, char>, int> pam_matrix = {};
    for (char c1 = '0'; c1<= '3'; c1++) {
        for (char c2 = '0'; c2<= '3'; c2++) {
            std::tuple<char, char> pamTouple = std::make_tuple(c1, c2);
            if (c1 == c2) {
                pam_matrix.insert( std::pair<std::tuple<char, char>,int>(pamTouple, 0) );
            } else if (abs(c1 - c2) == 2) {
                pam_matrix.insert( std::pair<std::tuple<char, char>,int>(pamTouple, SequenceMapper::missmatch_1) );
            } else {
                pam_matrix.insert( std::pair<std::tuple<char, char>,int>(pamTouple, SequenceMapper::missmatch_2) );
            }
        }
    }
    return pam_matrix;
}

std::map<std::tuple<char, char>, int> SequenceMapper::pam = initPam();

std::vector<unsigned int> SequenceMapper::getMatchingPositions(Sequence &sequence_A, Sequence &sequence_B) {
  std::vector<unsigned int> positions{};

  for (const KmerTriple& kmer_triple : sequence_B.getMinimizers()) {
        int k = kmer_triple.GetKey().getKmer().Length();
        bool is_on_reverse_helix = kmer_triple.GetKey().isOnReverseHelix();
        unsigned int position_B = kmer_triple.GetPosition();
        //std::map<char, char> reverse_nucleobase = {{'0', '3'}, {'1', '2'}, {'2', '1'}, {'3', '0'}};

        KmerKey key_true{kmer_triple.GetKey().getKmer(), false};
        KmerKey key_reverse{kmer_triple.GetKey().getKmer(), true};
        std::vector<unsigned int> positions_true = sequence_A.minimizer_index[key_true];
        std::vector<unsigned int> positions_reverse = sequence_A.minimizer_index[key_reverse];
        bool is_found_true = positions_true.size() >= 1;
        bool is_found_reverse = positions_reverse.size() >= 1;

        bool reverse_helix = !(is_found_reverse == is_on_reverse_helix);
        int reverse_hel = reverse_helix == true ? 1 : 0;

        if (is_found_true) {
            for (auto& position_A : positions_true) {
                int true_position = position_A;
                 for (int i=1; i<=5; i++) {
                    int pos_A_check = position_A - i;
                    int pos_B_check = position_B - i;
                    if (pos_A_check < 0 || pos_B_check < 0)
                        continue;

                    if (sequence_A.getSequence()[pos_A_check] != sequence_B.getSequence()[pos_B_check]) {
                        true_position = -1;
                        break;
                    }

                    pos_A_check = position_A + k + i;
                    pos_B_check = position_B + k + i;
                    if (pos_A_check >= (int)sequence_A.getSequence().Length() || pos_B_check >= (int)sequence_B.getSequence().Length())
                        continue;

                    if (sequence_A.getSequence()[pos_A_check] != sequence_B.getSequence()[pos_B_check]) {
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
                 for (int i=1; i<=5; i++) {
                    int pos_A_check = position_A - i;
                    int pos_B_check = position_B - i;
                    if (pos_A_check < 0 || pos_B_check < 0)
                        continue;

                    if (reverse_nucleobase[sequence_A.getSequence()[pos_A_check]] != sequence_B.getSequence()[pos_B_check]) {
                        true_position = -1;
                        break;
                    }

                    pos_A_check = position_A + k + i;
                    pos_B_check = position_B + k + i;
                    if (pos_A_check >= (int)sequence_A.getSequence().Length() || pos_B_check >= (int)sequence_B.getSequence().Length())
                        continue;

                    if (reverse_nucleobase[sequence_A.getSequence()[pos_A_check]] != sequence_B.getSequence()[pos_B_check]) {
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

cell get_cell(int cost, int i, int j) {
    cell c;
    c.cost = cost;
    c.parrent_x = i;
    c.parrent_y = j;
    return c;
}

std::list<mutation> SequenceMapper::getGlobalMutations(Sequence &sequence_A, Sequence &sequence_B,
                                                        int position_A, int N, int position_B, int M, bool reverse_helix) {
    std::list<mutation> mutations{};
    int kN = M/100;

    std::map<std::tuple<int, int>, cell> m;

    cell c_init = {0,-1,-1};

    std::tuple<int, int> m_position_init = std::make_tuple(0, 0);
    m.insert( std::pair<std::tuple<int, int>, cell>(m_position_init, c_init) );

    std::cout << "kN = " << kN << "; m.size = " << m.size() << std::endl;

    for (int i = 1; i<= kN; i++) {
        std::tuple<int, int> m_position_1 = std::make_tuple(0, i);
        std::tuple<int, int> m_position_2 = std::make_tuple(i, 0);

        cell c1 = {i * SequenceMapper::indel, 0, i-1};
        cell c2 = {i * SequenceMapper::indel, i-1, 0};

        m.insert( std::pair<std::tuple<int, int>, cell>(m_position_1, c1) );
        m.insert( std::pair<std::tuple<int, int>, cell>(m_position_2, c2) );
    }

    std::cout << "m.size = " << m.size() << std::endl;

    int opt;
    std::tuple<int, int> *best_parrent;
    const CharVector &x = sequence_B.getSequence();
    const CharVector &y = sequence_A.getSequence();

    cell *goal_cell = &c_init;

    for (int i = 1; i <= M; i++) {
        for (int j = std::max(1, i-kN); j <= std::min(N, i + kN); j++) {

            std::tuple<int, int> m_position_match = std::make_tuple(i-1, j-1);
            std::tuple<int, int> m_position_insert = std::make_tuple(i, j-1);
            std::tuple<int, int> m_position_delete = std::make_tuple(i-1, j);

            opt = m[m_position_match].cost + SequenceMapper::pam[std::make_tuple(x[position_B + i-1], y[position_A + j-1])];
            best_parrent = &m_position_match;

            if (j > i-kN) {
                int test = m[m_position_insert].cost + SequenceMapper::indel;
                if (test < opt) {
                    opt = test;
                    best_parrent = &m_position_insert;
                }
            }
            if (j < i+kN) {
                int test = m[m_position_delete].cost + SequenceMapper::indel;
                if (test < opt) {
                    opt = test;
                    best_parrent = &m_position_insert;
                }
            }

            cell c = {opt, std::get<0>(*best_parrent), std::get<1>(*best_parrent)};

            if (c.parrent_x <= 0 && c.parrent_y <= 0) {
                std::cout << "weird_cell(cost, parent_x, parent_y) = " << c.cost << "," << c.parrent_x << "," << c.parrent_y <<
                " ; i,j = " << i << "," << j << std::endl;
            }

            if (i == M) {
                goal_cell = &c;
                //std::cout << "goal_cell(cost, parent_x, parent_y) = " << goal_cell->cost << "," << goal_cell->parrent_x << "," << goal_cell->parrent_y << std::endl;
            }

            if (i == 9520 && j == 9423) {
                std::cout << "very_weird_cell(cost, parent_x, parent_y) = " << c.cost << "," << c.parrent_x << "," << c.parrent_y <<
                    " ; i,j = " << i << "," << j << std::endl;
            }

            m.insert( std::pair<std::tuple<int, int>, cell>(std::make_tuple(i, j), c) );
        }
    }

    std::cout << "m.size = " << m.size() << std::endl;

    int maxN = std::min(N, M + kN);
    cell *current_cell = goal_cell;
    cell *parrent_cell = nullptr;
    int i = M, j = maxN;

    std::cout << "goal_cell(cost, parent_x, parent_y) = " << goal_cell->cost << "," << goal_cell->parrent_x << "," << goal_cell->parrent_y << std::endl;

    while (i >= 0 && j >= 0) {
        std::cout << "previous_cell(cost, parent_x, parent_y) = " << current_cell->cost << "," << current_cell->parrent_x <<
            "," << current_cell->parrent_y << std::endl;
        parrent_cell = &m[std::make_tuple(current_cell->parrent_x, current_cell->parrent_y)];

        if (parrent_cell->cost == current_cell->cost) {
            i = current_cell->parrent_x;
            j = current_cell->parrent_y;
            current_cell = parrent_cell;
            continue;
        }

        unsigned int pos_a = (unsigned int)(position_A + j);
        int pos_b = (int)position_B + i;

        if (i - current_cell->parrent_x == 1 && j - current_cell->parrent_y == 1) {
            mutation mutt{'X', pos_a, reverse_nucleobase[x[pos_b]]};
            mutations.push_front(mutt);
        } else if (i - current_cell->parrent_x == 1 && j - current_cell->parrent_y == 0) {
            mutation mutt{'D', pos_a, '-'};
            mutations.push_front(mutt);
        } else if (i - current_cell->parrent_x == 0 && j - current_cell->parrent_y == 1) {
            mutation mutt{'I', pos_a, reverse_nucleobase[x[pos_b]]};
            mutations.push_front(mutt);
        }

        i = current_cell->parrent_x;
        j = current_cell->parrent_y;
        current_cell = parrent_cell;
    }

    std::cout << "starting_cell(cost, parent_x, parent_y) = " << current_cell->cost << "," << current_cell->parrent_x <<
        "," << current_cell->parrent_y << std::endl;

    current_cell = &m[std::make_tuple(9527, 9431)];
    while (current_cell->parrent_x >= 0 && current_cell->parrent_y >= 0) {
        std::cout << "check_cell(cost, parent_x, parent_y) = " << current_cell->cost << "," << current_cell->parrent_x <<
            "," << current_cell->parrent_y << std::endl;
        current_cell = &m[std::make_tuple(current_cell->parrent_x, current_cell->parrent_y)];
    }

    m.clear();

    return mutations;
}

std::list<mutation> SequenceMapper::getMutations(Sequence &sequence_A, Sequence &sequence_B) {

    std::vector<unsigned int> positions = this->getMatchingPositions(sequence_A, sequence_B);
    if (positions.size() == 0) {
        std::list<mutation> mutts{};
        return mutts;
    }

    int k = positions[3];
    bool reverse_helix = (positions[2] == 1);
    int position_A = positions[0] + k + 1;
    int position_B = positions[1] + k + 1;
    int N = sequence_A.getSequence().Length() - position_A;
    int M = sequence_B.getSequence().Length() - position_B;

    std::cout << "pos_A = " << position_A << "; pos_B = " << position_B << "; N = " << N << "; M = " << M << std::endl;

    std::list<mutation> mutations = getGlobalMutations(sequence_A, sequence_B, position_A, N, position_B, M, reverse_helix);

    return mutations;
}
