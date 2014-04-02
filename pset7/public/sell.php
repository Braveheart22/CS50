<?php

    // configuration
    require("../includes/config.php");

    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["stockList"]))
        {
            apologize("You must select a stock symbol to sell...");
        }
        else if (lookup($_POST["stockList"]) === false)
        {
            apologize("Symbol (" . $_POST["symbol"] . ") not found.");
        }

        $stock = lookup($_POST["stockList"]);
        $rows = query("SELECT shares FROM portfolio WHERE id = ? and symbol = ?", $_SESSION["id"], $stock["symbol"]);
        $stockToSell = [
            "price" => $stock["price"],
            "shares" => $rows[0]["shares"],
            "symbol" => $stock["symbol"]
        ];

        $rows = query("DELETE FROM portfolio WHERE id = ? and symbol = ?", $_SESSION["id"], $stock["symbol"]);
        if ($rows !== false)
        {
            $rows = query("UPDATE users SET cash = cash + ? WHERE id = ?", ($stockToSell["shares"] * $stockToSell["price"]), $_SESSION["id"]);
            if ($rows !== false)
            {
                render("sell.php", ["title" => "Sold", "stockToSell" => $stockToSell]);
            }
            else
            {
                apologize("Error updating cash in USER table.");
            }
        }
        else
        {
            apologize("Error deleting from PORTFOLIO table.");
        }
        
    }
    else
    {
        $rows = query("SELECT symbol FROM portfolio WHERE id = ? ORDER BY symbol", $_SESSION["id"]);
        render("sell_form.php", ["title" => "Sell Stock", "stocks" => $rows]);
    }
    
?>
