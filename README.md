# first-project
Cafeteria Management System
# 🍽️ Cafeteria Management System Using C

## 📌 Project Overview

The **Cafeteria Management System** is a menu-driven, console-based application developed using the C programming language. It helps manage cafeteria food orders, customer details, billing, and sales records.

The system allows customers to select food items, enter quantities, and receive a bill automatically. It also stores order details in a text file so that previous orders can be viewed and searched later.

This project demonstrates fundamental C programming concepts such as structures, arrays, functions, loops, conditional statements, and file handling.

## 🎯 Objectives

* To develop a simple cafeteria management application using C.
* To display food items and their prices.
* To accept customer orders containing multiple food items.
* To calculate item subtotals and the final bill automatically.
* To store customer order details permanently in a text file.
* To search for orders using an order ID or customer name.
* To calculate total cafeteria sales.

## ✨ Features

### 1. Display Food Menu

Displays the available food items, their IDs, and prices.

### 2. Place Customer Orders

* Accepts the customer's name.
* Generates a unique order ID based on existing saved orders.
* Allows multiple food items in a single order.
* Accepts the quantity of each item.
* Calculates the subtotal and grand total.
* Displays a detailed bill with the order date and customer information.

### 3. Store Order Details

Saves completed orders in `orders.txt` using C file handling.

Each saved order contains:

* Order ID
* Customer name
* Date and time
* Food item IDs and names
* Quantities
* Item prices
* Item subtotals
* Grand total

New orders are appended to the file without overwriting existing records.

### 4. View All Orders

Displays the customer orders stored in the file.

### 5. Search by Order ID

Searches for a specific order using its unique order ID.

### 6. Search by Customer Name

Finds orders associated with a customer name. The search is case-insensitive and can match part of a name.

### 7. Calculate Total Sales

Displays the number of saved orders, total sales revenue, and average order value.

### 8. Input Validation

Checks menu choices, food item IDs, and quantities to help prevent invalid inputs.

## 🍔 Sample Food Menu

| Item ID | Food Item   | Price |
| ------- | ----------- | ----: |
| 1       | Idli        |   ₹30 |
| 2       | Dosa        |   ₹50 |
| 3       | Poori       |   ₹40 |
| 4       | Veg Meals   |  ₹100 |
| 5       | Fried Rice  |   ₹80 |
| 6       | Sandwich    |   ₹60 |
| 7       | Tea         |   ₹15 |
| 8       | Coffee      |   ₹20 |
| 9       | Fresh Juice |   ₹40 |

*Note: These are predefined sample prices and can be modified in the source code.*

## 🛠️ Technologies Used

* **Programming Language:** C
* **Compiler:** GCC or another compatible C compiler
* **Development Environment:** Visual Studio Code, Code::Blocks, or another C IDE
* **Data Storage:** Text file (`orders.txt`)
* **Programming Concepts:** Structures, arrays, functions, loops, conditional statements, strings, and file handling

## 📂 Project Structure

```text
Cafeteria-Management-System/
│
├── cafeteria.c    # Main C source code
├── orders.txt     # Customer order records (created when orders are saved)
└── README.md      # Project documentation
```

**Note:** The `orders.txt` file is created when the program successfully saves its first order. If you want to include it in your repository, you can add a sample file separately.

## ⚙️ Installation and Execution

### Step 1: Clone the Repository

Open a terminal and run:

```bash
git clone YOUR_GITHUB_REPOSITORY_URL
```

Replace `YOUR_GITHUB_REPOSITORY_URL` with your actual repository URL.

### Step 2: Open the Project Folder

```bash
cd Cafeteria-Management-System
```

### Step 3: Compile the Program

Make sure GCC is installed and available in your terminal.

Run:

```bash
gcc cafeteria.c -o cafeteria
```

### Step 4: Run the Program

**Windows:**

```bash
cafeteria.exe
```

**Linux or macOS:**

```bash
./cafeteria
```

### Step 5: Use the Application

Select an option from the main menu:

1. Display Food Menu
2. Place Customer Order
3. View All Customer Orders
4. Search Order by Order ID
5. Search Orders by Customer Name
6. Calculate Total Sales
7. Exit

Follow the prompts displayed in the terminal.

## 💻 Sample Output

```text
==================================================
     WELCOME TO CAFETERIA MANAGEMENT SYSTEM
==================================================

------------------- MAIN MENU --------------------
1. Display Food Menu
2. Place Customer Order
3. View All Customer Orders
4. Search Order by Order ID
5. Search Orders by Customer Name
6. Calculate Total Sales
7. Exit

Enter your choice (1-7): 2

Enter Customer Name: Rahul

Select food item ID: 2
Selected: Dosa | Price: Rs. 50.00
Enter quantity: 2

Select another item? (1 = Yes, 0 = No): 0

                  ORDER SUMMARY
Order ID      : 1001
Customer Name : Rahul

Item  Quantity  Price  Subtotal
Dosa     2      50.00   100.00

Grand Total: Rs. 100.00

[SUCCESS] Order #1001 saved successfully to 'orders.txt'!
```

*The output above is an illustrative example. Actual dates, order IDs, and displayed formatting may vary.*

## 🧠 Concepts Demonstrated

| Concept                | Application                                      |
| ---------------------- | ------------------------------------------------ |
| Structures             | Store menu items and customer order information  |
| Arrays                 | Manage menu items and multiple items in an order |
| Functions              | Separate the program into manageable modules     |
| Loops                  | Display menus and process repeated operations    |
| Conditional Statements | Validate input and control program flow          |
| Strings                | Handle customer names and food item names        |
| File Handling          | Save and retrieve order records                  |
| Time Functions         | Record the current date and time                 |
| Searching              | Find orders by ID or customer name               |

## 🔮 Future Enhancements

* Add an administrator login system.
* Allow administrators to add, update, or remove food items.
* Generate printable bills and receipts.
* Add order cancellation and refund management.
* Store records in a database such as MySQL or SQLite.
* Develop a graphical user interface.
* Add daily and monthly sales reports.
* Add inventory management to track food availability.

## 🎓 Project Purpose

This project is intended for learning and demonstrating fundamental C programming concepts through a practical, real-world-style application. It can be used as a college mini project for introductory programming coursework.

## 👨‍💻 Author

**Name:** Your Name

**Course:** Your Course Name

**Department:** Your Department

**Institution:** Your College Name

## 📄 License

This project is intended for educational purposes. You may add an appropriate open-source license if you wish to allow others to reuse or modify the code.
