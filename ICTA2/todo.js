const readline = require("readline");

const tasks = [];

function addTask() {
    input.question("Enter a task: ", (task) => {
        if (!task.trim()) {
            console.log("Task cannot be empty.");
        } else {
            tasks.push(task.trim());
            console.log("Task added.");
        }
        askForCommand();
    });
}

function removeTask() {
    if (tasks.length === 0) {
        console.log("There are no tasks to remove.");
        askForCommand();
        return;
    }

    displayTasks();
    input.question("Enter the task number to remove: ", (answer) => {
        const index = Number.parseInt(answer, 10);
        if (!Number.isInteger(index) || index < 1 || index > tasks.length) {
            console.log("Invalid task number.");
        } else {
            console.log(`Removed: ${tasks.splice(index - 1, 1)[0]}`);
        }
        askForCommand();
    });
}

function displayTasks() {
    if (tasks.length === 0) {
        console.log("Your to-do list is empty.");
        return;
    }

    console.log("\nTo-do list:");
    tasks.forEach((task, index) => console.log(`${index + 1}. ${task}`));
}

function clearTasks() {
    tasks.length = 0;
    console.log("All tasks cleared.");
}

const input = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

function askForCommand() {
    input.question("\nEnter a command (add, remove, view, clear, or exit): ", (command) => {
        switch (command.trim().toLowerCase()) {
            case "add":
                addTask();
                break;
            case "remove":
                removeTask();
                break;
            case "view":
                displayTasks();
                askForCommand();
                break;
            case "clear":
                clearTasks();
                askForCommand();
                break;
            case "exit":
                input.close();
                break;
            default:
                console.log("Unknown command. Choose add, remove, view, clear, or exit.");
                askForCommand();
        }
    });
}

console.log("To-do list manager");
askForCommand();
