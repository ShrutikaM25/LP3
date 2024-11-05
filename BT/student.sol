// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

contract StudManagement {
    struct Student {
        uint id;
        string name;
        uint age;
        string course;
    }

    Student[] public stud;

    mapping(uint => bool) public StudExists;

    event StudentAdded(uint id, string name, uint age, string course);
    event FallBackTrigger(address sender, uint amount, string message);

    function add_stud(uint _id, string memory _name, uint _age, string memory _course) public {
        require(!StudExists[_id], "Student with that ID already exists!");

        Student memory newStud = Student({
            id: _id,
            name: _name,
            age: _age,
            course: _course
        });

        stud.push(newStud);
        StudExists[_id] = true;

        emit StudentAdded(_id, _name, _age, _course);
    }

    function tot_student() public view returns (uint) {
        return stud.length;
    }

    function getStud(uint _index) public view returns (uint, string memory, uint, string memory) {
        require(_index < stud.length, "Invalid student index!");

        Student memory s = stud[_index];

        return (s.id, s.name, s.age, s.course);
    }

    fallback() external payable {
        emit FallBackTrigger(msg.sender, msg.value, "Fallback triggered!");
    }

    receive() external payable {
        emit FallBackTrigger(msg.sender, msg.value, "Receive function triggered!");
    }
}
