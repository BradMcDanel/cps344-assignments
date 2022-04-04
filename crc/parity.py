def compute_parity_bit(data):
    """
    Compute parity bit for even parity (after number of 1's is even)
    """
    pass



def parity_check(data):
    """
    Checks if even parity is preserved (number of 1's is even)
    """
    pass


if __name__=='__main__':
    data = [1, 0, 1, 1, 0, 1, 0]
    parity_bit = compute_parity_bit(data)

    # Simulate no error in channel
    data.append(parity_bit)
    print('Data is ok?', parity_check(data))

    # Simulate error in channel
    data[0] = 0
    print('Data is ok?', parity_check(data))

