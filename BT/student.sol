//
pragma solidity ^0.8.0;

contract StudentRegistry {
    struct Student {
        string name;
        uint rollNo;
        string course;
    }

    Student[] public students;
    mapping(uint => uint) private rollNoToIndex;
    uint public studentCount;

    // Events for logging
    event StudentAdded(string name, uint rollNo, string course);
    event EtherReceived(address sender, uint amount);
    event FallbackTriggered(address sender, uint amount);

    // Function to add a new student
    function addStudent(string memory name, uint rollNo, string memory course) public {
        require(rollNoToIndex[rollNo] == 0, "Student with this roll number already exists");
        students.push(Student(name, rollNo, course));
        rollNoToIndex[rollNo] = students.length; // Store index + 1 to differentiate from default value
        studentCount++;
        emit StudentAdded(name, rollNo, course);
    }

    // Function to get a student by roll number
    function getStudentByRollNo(uint rollNo) public view returns (string memory name, uint rollNoOut, string memory course) {
        uint index = rollNoToIndex[rollNo];
        require(index > 0, "Student with this roll number does not exist");
        Student storage student = students[index - 1];
        return (student.name, student.rollNo, student.course);
    }

    // Function to get the total list of students
    function getAllStudents() public view returns (Student[] memory) {
        return students;
    }

    // Fallback function to handle unexpected function calls
    fallback() external payable {
        emit FallbackTriggered(msg.sender, msg.value);
    }

    // Receive function to accept Ether
    receive() external payable {
        emit EtherReceived(msg.sender, msg.value);
    }
}