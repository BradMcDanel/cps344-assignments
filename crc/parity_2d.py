def compute_parity_bit(data):
    """
    Compute parity bit for even parity (after number of 1's is even)
    """
    num_ones = 0
    for i in range(len(data)):
        if data[i] == 1:
            num_ones += 1

    if num_ones % 2 == 0:
        return 0
    else:
        return 1


def parity_check(data):
    """
    Checks if even parity is preserved (number of 1's is even)
    """
    num_ones = 0
    for i in range(len(data)):
        if data[i] == 1:
            num_ones += 1

    return num_ones % 2 == 0


if __name__=='__main__':
    data = [
        [1, 0, 1, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 1, 0],
        [0, 1, 1, 1, 0, 0, 1],
        [1, 0, 1, 0, 1, 1, 0],
    ]


    parity_bit = compute_parity_bit(data)

    # Simulate no error in channel
    data.append(parity_bit)
    print('Data is ok?', parity_check(data))

    # Simulate error in channel
    data[0] = 0
    print('Data is ok?', parity_check(data))

