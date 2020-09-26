#include "permutations.h"

#include <vector>
#include <algorithm>
#include <iostream>

#include "utils.h"

using namespace std;

void assemble_from_alph(vector<int> in_remain_alphabet, vector<int> in_cur_arr,
		vector<vector<int>> &solution_array) {
	static int sol_cnt = 0;
	if (0 == in_cur_arr.size()) {
		sol_cnt = 0;
	}
	if (0 == in_remain_alphabet.size()) {
		if (0 < in_cur_arr.size()) {
			solution_array.push_back(in_cur_arr);
			sol_cnt++;
		}
	} else if (0 < in_remain_alphabet.size()) {
		for (int num_order = 0; num_order < in_remain_alphabet.size();
				num_order++) {
			vector<int> new_remain_alphabet = in_remain_alphabet;
			int add_val = new_remain_alphabet[num_order];
			vector<int> cur_array_extended = in_cur_arr;
			cur_array_extended.push_back(add_val);

			vector<int> redused_alphabet = new_remain_alphabet;
			redused_alphabet.erase(redused_alphabet.begin() + num_order);
			assemble_from_alph(redused_alphabet, cur_array_extended,
					solution_array);
		}
	}
}

vector<vector<int>> permute(vector<int> &nums) {
	vector<vector<int>> output;
	vector<int> cur_sol;
	assemble_from_alph(nums, cur_sol, output);
	return output;
}

