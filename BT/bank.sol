// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

contract BankAccount {
    // State variables
    address public owner;
    uint public balance;

    // Constructor
    constructor() {
        owner = msg.sender;
    }

    // Functions
    function deposit(uint amount) public {
        balance += amount;
    }

    function withdraw(uint amount) public {
        require(balance >= amount, "Insufficient balance");
        balance -= amount;
    }

    function getBalance() public view returns (uint) {
        return balance;
    }
}