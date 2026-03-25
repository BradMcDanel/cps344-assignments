switch_table = {}   # mac -> port
ports = [0, 1, 2, 3]


def process_frame(src_mac, dst_mac, in_port):
    # TODO: implement self-learning switch logic
    # 1. learn: record src_mac -> in_port in switch_table
    # 2. if dst_mac is known, return [that port]
    # 3. otherwise, return all ports except in_port (flood)
    pass


if __name__ == "__main__":
    # A sends to B -- switch doesn't know B yet, should flood
    out = process_frame("MAC_A", "MAC_B", 0)
    print("A->B (port 0): " + str(out) + "  table: " + str(switch_table))

    # B replies to A -- switch knows A (port 0), should unicast
    out = process_frame("MAC_B", "MAC_A", 2)
    print("B->A (port 2): " + str(out) + "  table: " + str(switch_table))

    # C sends to B -- switch knows B (port 2), should unicast
    out = process_frame("MAC_C", "MAC_B", 1)
    print("C->B (port 1): " + str(out) + "  table: " + str(switch_table))

    # Expected:
    #   A->B: [1, 2, 3]  (flood)
    #   B->A: [0]        (unicast)
    #   C->B: [2]        (unicast)
