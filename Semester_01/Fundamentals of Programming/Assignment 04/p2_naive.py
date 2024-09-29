# Determine the longest common subsequence of two given sequences. Subsequence elements are not required to occupy consecutive positions. For example, if X = "MNPNQMN" and Y = "NQPMNM", the longest common subsequence has length 4, and can be one of "NQMN", "NPMN" or "NPNM". Determine and display both the length of the longest common subsequence as well as at least one such subsequence.


# return condition: if either of the sequences is empty the length of the lcs is 0 and the lcs string is an empty string. if the last elements of both sequences match we recursively find the lcs of the sequences without these last elements and append the matching element to the lcs string. if the last elements !match, we consider two cases: Recursively find the lcs by excluding the last element of sequence 1 and recursively find the lcs by excluding the last element of sequence 2 --> return the lcs with the greater length among the two cases.

# time complexity : O(2 ** (len(first_sequence)+len(second_sequence)) -- exponential

# Author: Rares Cotoi, @ 912

def naive_implementation_of_searching_for_the_longest_common_subsequence_between_two_given_sequences(
        first_given_sequence, second_given_sequence, length_of_the_first_given_sequence,
        length_of_the_second_given_sequence):
    if length_of_the_first_given_sequence == 0 or length_of_the_second_given_sequence == 0:
        return 0, ""
    elif first_given_sequence[length_of_the_first_given_sequence - 1] == second_given_sequence[
        length_of_the_second_given_sequence - 1]:
        lcs_length, lcs_str = naive_implementation_of_searching_for_the_longest_common_subsequence_between_two_given_sequences(
            first_given_sequence, second_given_sequence, length_of_the_first_given_sequence - 1,
                                                         length_of_the_second_given_sequence - 1)
        return lcs_length + 1, lcs_str + first_given_sequence[length_of_the_first_given_sequence - 1]
    else:
        lcs1_length, lcs1_str = naive_implementation_of_searching_for_the_longest_common_subsequence_between_two_given_sequences(
            first_given_sequence, second_given_sequence, length_of_the_first_given_sequence - 1,
            length_of_the_second_given_sequence)
        lcs2_length, lcs2_str = naive_implementation_of_searching_for_the_longest_common_subsequence_between_two_given_sequences(
            first_given_sequence, second_given_sequence, length_of_the_first_given_sequence,
            length_of_the_second_given_sequence - 1)
        if lcs1_length > lcs2_length:
            return lcs1_length, lcs1_str
        else:
            return lcs2_length, lcs2_str


def main():
    first_given_sequence = input("Enter the first sequence: ")
    second_given_sequence = input("Enter the second sequence: ")
    length_of_the_result_subsequence, result_subsequence = naive_implementation_of_searching_for_the_longest_common_subsequence_between_two_given_sequences(
        first_given_sequence, second_given_sequence, len(first_given_sequence), len(second_given_sequence))
    print("Length of LCS:", length_of_the_result_subsequence)
    print("LCS Subsequence:", result_subsequence)


if __name__ == "__main__":
    main()
