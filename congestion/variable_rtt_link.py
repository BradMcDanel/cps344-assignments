import conn
from packet_data import packets

if __name__=='__main__':
    pconn = conn.VariableRTTConnection(min_RTT=1, max_RTT=10)
    ack_packets = set()
    send_idx = 0

    while len(ack_packets) < len(packets):
        # print connection state
        print(pconn)

        # send one new packet per tick (while there are packets to send)
        if send_idx < len(packets):
            pconn.send(packets[send_idx])
            send_idx += 1

        # get the acks
        acks = pconn.get_acks()
        for ack in acks:
            ack_packets.add(ack)

        # print the acks
        if len(acks) > 0:
            print("ACKs")
            for ack in acks:
                print("- " + ack)

        print()

        # tick simulates one unit of time passing
        pconn.tick()
