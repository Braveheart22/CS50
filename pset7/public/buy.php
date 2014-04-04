<?php

    // configuration
    require("../includes/config.php");

    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate stock symbol
        if (empty($_POST["symbol"]))
        {
            apologize("You must enter a stock symbol to buy...");
        }
        else if (lookup($_POST["symbol"]) === false)
        {
            apologize("Symbol (" . $_POST["symbol"] . ") not found.");
        }

        // validate number of shares to buy
        if (empty($_POST["shares"]))
        {
            apologize("You must enter the amount of shares to buy...");
        }
        else if (!preg_match("/^\d+$/", $_POST["shares"]))
        {
            apologize("You must enter a whole integer of shares to buy.");
        }
        
        // Get stock to buy info
        $stock = lookup($_POST["symbol"]);
        // Get amount of money user has to spend
        $rows = query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
        // Make sure users has enough money to buy the stocks
        if (($stock["price"] * $_POST["shares"]) > $rows[0]["cash"])
        {
            apologize("You don't have enough money to buy " .  $stock["symbol"] . ".");
        }

        // Enter the new purchase into the users' portfolio
        $rows = query("INSERT INTO portfolio (id, symbol, shares) VALUES (?, ?, ?) ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)", $_SESSION["id"], strtoupper ($stock["symbol"]), $_POST["shares"]);
        if ($rows !== false)
        {
            // Update the users' cash
            $rows = query("UPDATE users set cash = cash - ? where id = ?", ($stock["price"] * $_POST["shares"]), $_SESSION["id"]);
            if ($rows !== false)
            {
                // Update history
                $rows = query("INSERT INTO history (id, transaction_type, symbol, shares, price) VALUES (?, ?, ?, ?, ?)", $_SESSION["id"], "BUY", strtoupper ($stock["symbol"]), $_POST["shares"], $stock["price"]);
                if ($rows !== false)
                {
                    redirect("/");
                }
                else
                {
                    apologize("Error updating trading history.");
                }
            }
            else
            {
                apologize("Error updating cash in USER table.");
            }
        }
        else
        {
            apologize("Error inserting rows in PORTFOLIO table.");
        }
    }
    else
    {
        render("buy_form.php", ["title" => "Buy Stock"]);
    }
    
?>
