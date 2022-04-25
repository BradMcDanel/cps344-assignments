from hashlib import sha256
import datetime


class Block:
    def __init__(self, index, previous_hash, timestamp, data):
        self.index = index
        self.previous_hash = previous_hash
        self.timestamp = timestamp
        self.data = data
        self.nonce = 0


def hash_block(block, nonce):
    """
    Creates a SHA256 hash of a block
    """
    return sha256((str(block.index) + str(block.previous_hash) + str(block.timestamp) + str(block.data) + str(nonce)).encode()).hexdigest()


if __name__=='__main__':
    block_a = Block(0,
                    '', # no previous hash for the first block
                    datetime.datetime.now(), # timestamp
                    # transaction data
                    [
                        'a gave $5 to b',
                        'c gave $10 to d',
                    ]
              )

    # TODO: mine the block (find the nonce that produces a hash with leading zeros = difficulty)
    #     : try different difficuly levels (1, 2, 3, 4) number of leading zeros
    # example hash  (rewrite this to mine a block)
    output = hash_block(block_a, 0)
    print(output)

    # TODO: After mining, try to create a new block and add it to the chain (using previous_hash)
