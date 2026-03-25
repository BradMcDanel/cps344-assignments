# Topology: Host A -- Router -- Host B
#   10.0.0.2  Host A
#   10.0.0.1  Router
#   10.0.0.3  Host B

# ARP tables: for each node (by IP), maps next-hop IP -> MAC
ARP_TABLES = {
    "10.0.0.2": {"10.0.0.1": "1A:23:F9:CD:06:9B"},  # Host A knows the router's MAC
    "10.0.0.1": {"10.0.0.3": "AA:BB:CC:DD:EE:FF"},  # Router knows Host B's MAC
}

# each node's own MAC
MY_MAC = {
    "10.0.0.2": "74:A0:9C:E8:FF:55",
    "10.0.0.1": "49:BD:D2:C7:56:2A",
}


def prepare_frame(node_ip, next_hop_ip, frame):
    # TODO: set frame["src_mac"] and frame["dst_mac"] for the next hop
    # src_ip and dst_ip must not change
    pass


def print_frame(frame, location):
    print("[" + location + "]")
    print("  IP  : " + str(frame["src_ip"]) + " -> " + str(frame["dst_ip"]))
    print("  MAC : " + str(frame["src_mac"]) + " -> " + str(frame["dst_mac"]))
    print()


if __name__ == "__main__":
    frame = {
        "src_ip":  "10.0.0.2",
        "dst_ip":  "10.0.0.3",
        "src_mac": None,
        "dst_mac": None,
        "payload": "Hello, Host B!",
    }

    prepare_frame("10.0.0.2", "10.0.0.1", frame)
    print_frame(frame, "Leaving Host A")

    prepare_frame("10.0.0.1", "10.0.0.3", frame)
    print_frame(frame, "Leaving Router")

    # Expected:
    #   [Leaving Host A]
    #     IP  : 10.0.0.2 -> 10.0.0.3
    #     MAC : 74:A0:9C:E8:FF:55 -> 1A:23:F9:CD:06:9B
    #
    #   [Leaving Router]
    #     IP  : 10.0.0.2 -> 10.0.0.3    <- unchanged!
    #     MAC : 49:BD:D2:C7:56:2A -> AA:BB:CC:DD:EE:FF
