def cdma_encode(bits, codebook):
    output = []
    # TODO: multiply each bit by each element of the codebook
    #     : and append to output
    
    return output

def cdma_decode(encoded_bits, codebook):
    # TODO: multiply each encoded bit by the corresponding element of the codebook
    #     : then sum and round to recover a single input bit. Repeat for all bits.
    bits = []

    return bits


def elem_add(list1, list2):
    # helper function to add lists together - useful for test_multiple
    output = []
    for i in range(len(list1)):
        output.append(list1[i] + list2[i])
    return output


def test_single():
    codebook = [1, -1, -1, 1]
    inp = [1, 0, 1]

    enc = cdma_encode(inp, codebook)
    print('Encoded bits:', enc)

    dec = cdma_decode(enc, codebook)

    print(f'Input bits: {inp}, Decoded bits: {dec}')

    
def test_multiple():
    # test codebooks
    codebook_1 = [1,  1,  1,  1]
    codebook_2 = [1, -1,  1, -1]
    codebook_3 = [1,  1, -1, -1]
    codebook_4 = [1, -1, -1,  1]

    inp_1 = [0, 0, 1]
    inp_2 = [0, 1, 0]
    inp_3 = [0, 1, 1]
    inp_4 = [1, 0, 0]

    # encoding phase
    enc_1 = cdma_encode(inp_1, codebook_1)
    # TODO: encode inp_2, inp_3, inp_4 using codebook_2, codebook_3, codebook_4
    # TODO: add the encoded bits together single list (enc)
    enc = None
    
    print('Encoded bits:', enc)

    # decoding phase
    dec_1 = cdma_decode(enc, codebook_1)
    # TODO: recover inp_2, inp_3, inp_4 using codebook_2, codebook_3, codebook_4

    print(f'Input bits: {inp_1}, Decoded bits: {dec_1}')
    # print the recovered bits


if __name__=='__main__':
    test_single()
    test_multiple()
