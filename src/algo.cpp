#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include "algo.h"

std::vector<std::vector<int>> decode_state(const std::string& state) {
    std::vector<std::vector<int>> result;
    result.push_back(std::vector<int>());
    for (int i = 0; i < state.size(); i++) {
        if (state[i] == '|') {
            result.push_back(std::vector<int>());
        } else {
            result.back().push_back(state[i] - '0');
        }
    } 
    return result;
}

std::string encode_state(const std::vector<std::vector<int>>& array) {
    std::vector<std::string> strs;
    for (int i = 0; i < array.size(); i++) {
        std::string cur_str = "";
        for (int j = 0; j < array[i].size(); j++) {
            cur_str += '0' + array[i][j];
        }
        if (cur_str != "") {
            strs.push_back(cur_str);
        }
    }
    std::sort(strs.begin(), strs.end());
    std::string result = "";
    for (int i = 0; i < strs.size(); i++) {
        result += strs[i];
        if (i != strs.size() - 1) {
            result += '|';
        }
    }
    return result;
}

std::string normalize(const std::string& state) {
    std::vector<std::vector<int>> arr = decode_state(state);
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i].size() >= 9) {
            bool flag = true;
            for (int k = 0; k < 9; k++) {
                if (arr[i][arr[i].size() - 1 - k] != k + 1) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                for (int k = 0; k < 9; k++) {
                    arr[i].pop_back();
                }
            }
        }
    }
    return encode_state(arr);
}


std::vector<std::string> get_edges(std::string& state) {
    std::vector<std::vector<int>> arr = decode_state(state);
    std::vector<std::string> edges_ends;
    for (int i = 0; i < arr.size(); i++) {
        for (int j = 0; j < arr.size(); j++) {
            if (i == j || arr[j].back() <= arr[i].back()) continue;
            std::vector<std::vector<int>> copy_arr = arr;
            copy_arr[j].push_back(arr[i].back());
            copy_arr[i].pop_back();
            edges_ends.push_back(normalize(encode_state(copy_arr)));
        }
        if (arr.size() < 8) {
            std::vector<std::vector<int>> copy_arr = arr;
            copy_arr.push_back(std::vector<int>({arr[i].back()}));
            copy_arr[i].pop_back();
            edges_ends.push_back(normalize(encode_state(copy_arr)));
        }
    }
    return edges_ends;
}

std::pair<bool, size_t> find_solution(const std::string& state) {
    std::unordered_map<std::string, size_t> way_len;
    way_len[state] = 0;
    if (state == "") {
        return {true, way_len[state]};
    }
    std::queue<std::string> q;
    q.push(state);
    while (!q.empty()) {
        std::string head = q.front();
        std::vector<std::string> edges_ends = get_edges(head);
        q.pop();

        for (std::string new_state : edges_ends) {
            if (new_state == "") {
                return {true, way_len[head] + 1};
            }
            if (way_len.contains(new_state)) {
                continue;
            }
            way_len[new_state] = way_len[head] + 1;
            q.push(new_state);
        }
    }
    if (way_len.contains("")) {
        return {true, way_len[""]};
    } 
    return {false, -1};
}