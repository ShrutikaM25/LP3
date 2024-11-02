// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;
contract EVotingSystem {
    struct Candidate {
        string name;
        uint voteCount;
    }

    struct Voter {
        bool isRegistered;
        bool hasVoted;
        uint voteIndex;
    }

    address public admin;
    mapping(address => Voter) public voters;
    Candidate[] public candidates;
    bool public votingStarted;
    bool public votingEnded;

    // Events
    event VoterRegistered(address voter);
    event VoteCast(address voter, uint candidateIndex);
    event VotingStarted();
    event VotingEnded();

    // Constructor to initialize the contract with an admin
    constructor() {
        admin = msg.sender;
    }

    // Modifier to restrict access to only the admin
    modifier onlyAdmin() {
        require(msg.sender == admin, "Only admin can perform this action");
        _;
    }

    // Function to add a candidate
    function addCandidate(string memory name) public onlyAdmin {
        require(!votingStarted, "Cannot add candidates once voting has started");
        candidates.push(Candidate(name, 0));
    }

    // Function to start the voting
    function startVoting() public onlyAdmin {
        require(!votingStarted, "Voting has already started");
        require(!votingEnded, "Voting has already ended");
        votingStarted = true;
        emit VotingStarted();
    }

    // Function to end the voting
    function endVoting() public onlyAdmin {
        require(votingStarted, "Voting has not started yet");
        require(!votingEnded, "Voting has already ended");
        votingEnded = true;
        votingStarted = false;
        emit VotingEnded();
    }

    // Function to register a voter
    function registerVoter(address voter) public onlyAdmin {
        require(!voters[voter].isRegistered, "Voter is already registered");
        voters[voter] = Voter(true, false, 0);
        emit VoterRegistered(voter);
    }

    // Function to vote for a candidate
    function vote(uint candidateIndex) public {
        require(voters[msg.sender].isRegistered, "You are not registered to vote");
        require(!voters[msg.sender].hasVoted, "You have already voted");
        require(votingStarted, "Voting is not active");
        require(!votingEnded, "Voting has ended");
        require(candidateIndex < candidates.length, "Invalid candidate index");

        voters[msg.sender].hasVoted = true;
        voters[msg.sender].voteIndex = candidateIndex;
        candidates[candidateIndex].voteCount++;
        emit VoteCast(msg.sender, candidateIndex);
    }

    // Function to get candidate details
    // function getCandidate(uint candidateIndex) public view returns (string memory name, uint voteCount) {
    //     require(candidateIndex < candidates.length, "Invalid candidate index");
    //     return (candidates[candidateIndex].name, candidates[candidateIndex].voteCount);
    // }

    // Function to get total candidates count
    function getTotalCandidates() public view returns (uint) {
        return candidates.length;
    }
}