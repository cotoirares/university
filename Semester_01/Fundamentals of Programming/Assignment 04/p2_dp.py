"""
Determine the longest common subsequence of two given sequences. Subsequence elements are not required to occupy consecutive positions. For example, if X = "MNPNQMN" and Y = "NQPMNM", the longest common subsequence has length 4, and can be one of "NQMN", "NPMN" or "NPNM". Determine and display both the length of the longest common subsequence as well as at least one such subsequence.

dp approach: Initialize an array with dimensions [len(first_seq) + 1] [len(second_seq) + 1] and iterate through the sequences and fill the array based on the following algo:
if the current elements of the sequences matches, increment the length of the lcs by 1.
else, take the maximum of the lcs lengths obtained by excluding the current element from either sequence.
The final element of the array contains the length of the lcs.

to reconstruct the lcs, perform a traceback :
start from the bottom-right corner of the array.
if the current elements of the sequences matches, include this element in the lcs and move diagonally up-left.
if the lengths are equal, move left. if the lengths are different, move upward.

time complexity: O(len(first_seq) * len(second_seq))

Author: Rares Cotoi, @ 912
"""
def dynamic_implementation_of_searching_for_the_longest_common_subsequence_between_two_given_sequences(first_given_sequence, second_given_sequence):
    length_of_the_first_sequence = len(first_given_sequence)
    length_of_the_second_sequence = len(second_given_sequence)
    dynamic_array_for_longest_common_sequence_memorization = [[0] * (length_of_the_second_sequence+1) for _ in range(length_of_the_first_sequence+1)]

    for i in range(1, length_of_the_first_sequence+1):
        for j in range(1, length_of_the_second_sequence+1):
            if first_given_sequence[i - 1] == second_given_sequence[j - 1]:
                dynamic_array_for_longest_common_sequence_memorization[i][j] = dynamic_array_for_longest_common_sequence_memorization[i-1][j-1] + 1
            else:
                dynamic_array_for_longest_common_sequence_memorization[i][j] = max(dynamic_array_for_longest_common_sequence_memorization[i-1][j], dynamic_array_for_longest_common_sequence_memorization[i][j-1])

    length_of_the_longest_common_subsequence = dynamic_array_for_longest_common_sequence_memorization[length_of_the_first_sequence][length_of_the_second_sequence]
    the_longest_common_subsequence = ""

    #reconstruct the lcs
    i, j = length_of_the_first_sequence, length_of_the_second_sequence
    while i > 0 and j > 0:
        if first_given_sequence[i - 1] == second_given_sequence[j - 1]:
            the_longest_common_subsequence = first_given_sequence[i - 1] + the_longest_common_subsequence
            i -= 1
            j -= 1
        elif dynamic_array_for_longest_common_sequence_memorization[i-1][j] > dynamic_array_for_longest_common_sequence_memorization[i][j-1]:
            i -= 1
        else:
            j -= 1

    return length_of_the_longest_common_subsequence, the_longest_common_subsequence

def main():
    first_given_sequence = input("Enter the first sequence: ")
    second_given_sequence = input("Enter the second sequence: ")
    length_of_the_result_subsequence, result_subsequence = dynamic_implementation_of_searching_for_the_longest_common_subsequence_between_two_given_sequences(
        first_given_sequence, second_given_sequence)
    print("Length of LCS:", length_of_the_result_subsequence)
    print("LCS Subsequence:", result_subsequence)

if __name__ == "__main__":
    main()
