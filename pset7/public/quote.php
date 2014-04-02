<?php

    // configuration
    require("../includes/config.php");

    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["symbol"]))
        {
            apologize("You must provide stock quote to lookup...");
        }
        else if (lookup($_POST["symbol"]) === false)
        {
            apologize("Symbol (" . $_POST["symbol"] . ") not found.");
        }

        $stock = lookup($_POST["symbol"]);
        render("quote.php", ["title" => "Quote", "stock" => $stock]);
    }
    else
    {
        render("quote_form.php", ["title" => "Get Quote"]);
    }
    
?>
