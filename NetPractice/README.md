*This project has been created as part of the 42 curriculum by idiaz-ca.*

# NetPractice

## Description
Practical training project for network configuration and troubleshooting. Goal: provide a level-based interface to practice networking tasks (IP addressing, routing, VLANs, NAT, filtering, etc.) and to generate/export configurations per level.

## Instructions
- Run the training interface from the repository root:
  - `./run.sh`
- Export configurations (for submission or testing):
  - `./run.sh export`
  - or, if present, `./export_configs.sh`
- Expected export format: one file per level, named `level1.cfg`, `level2.cfg`, ..., `level10.cfg`.
- Submission requirement: place the 10 exported files (one per level) in the repository root.

## Resources
Networking concepts studied: TCP/IP (IPv4/IPv6 addressing), subnet masks, default gateways, routers and switches, OSI and TCP/IP models, VLANs, NAT, DHCP, DNS, ARP, routing tables and protocols (OSPF, RIP, BGP conceptually), sockets and ports.

Classic references:
- "Computer Networking: A Top-Down Approach" — Kurose & Ross
- RFC 791 (IPv4), RFC 793 (TCP), RFC 768 (UDP)
- Official Cisco documentation (routing/switching)
- Beej's Guide to Network Programming
- Documentation for iproute2 / netlink / iptables / nftables
- Tutorials and articles on MDN and Linux Networking HOWTOs

AI Usage:
- AI (GPT-5 mini) was used to generate and review this README, propose the structure of execution/export scripts, and review instructions. AI was not used to automatically solve the level exercises; practical solutions must be the student's work.

## Submission and verification
- Ensure the 10 exported files (`level1.json` ... `level10.json`) are in the repository root before submission.
- Include brief notes with the submission about any special steps to run your environment if they differ from the instructions above.

## Additional notes
Add usage examples, technical decisions, or links to specific scripts here if required by the evaluator.