# ARP tables: next-hop IP -> MAC address
ARP_TABLES = {
    "host_a": {
        "10.0.0.1": "1A:23:F9:CD:06:9B",   # router's left interface
    },
    "router": {
        "10.0.0.3": "AA:BB:CC:DD:EE:FF",    # host_b
    },
}

# each node's own MAC on its outgoing interface
MY_MAC = {
    "host_a": "74:A0:9C:E8:FF:55",
    "router": "49:BD:D2:C7:56:2A",
}


def prepare_frame(node, next_hop_ip, frame):
    # TODO: set frame["src_mac"] and frame["dst_mac"] for the next hop
    # src_ip and dst_ip must not change
    pass


def print_frame(frame, location):
    print("[" + location + "]")
    print("  IP  : " + str(frame["src_ip"]) + " -> " + str(frame["dst_ip"]))
    print("  MAC : " + str(frame["src_mac"]) + " -> " + str(frame["dst_mac"]))
    print()


if __name__ == "__main__":
    # topology: Host A (10.0.0.2) -- Router (10.0.0.1 | 10.0.0.1) -- Host B (10.0.0.3)
    frame = {
        "src_ip":  "10.0.0.2",
        "dst_ip":  "10.0.0.3",
        "src_mac": None,
        "dst_mac": None,
        "payload": "Hello, Host B!",
    }

    prepare_frame("host_a", "10.0.0.1", frame)
    print_frame(frame, "Leaving Host A")

    prepare_frame("router", "10.0.0.3", frame)
    print_frame(frame, "Leaving Router")

    # Expected:
    #   [Leaving Host A]
    #     IP  : 10.0.0.2 -> 10.0.0.3
    #     MAC : 74:A0:9C:E8:FF:55 -> 1A:23:F9:CD:06:9B
    #
    #   [Leaving Router]
    #     IP  : 10.0.0.2 -> 10.0.0.3    <- unchanged!
    #     MAC : 49:BD:D2:C7:56:2A -> AA:BB:CC:DD:EE:FF
