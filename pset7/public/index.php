<?php

    // configuration
    require("../includes/config.php"); 

    // render portfolio
    $rows = query("SELECT symbol, shares FROM portfolio WHERE id = ?", $_SESSION["id"]);
    $positions = [];

    foreach ($rows as $row)
    {
        $stock = lookup($row["symbol"]);
        if ($stock !== false)
        {
            $positions[] = [
                "name" => $stock["name"],
                "price" => $stock["price"],
                "shares" => $row["shares"],
                "symbol" => $row["symbol"]
            ];
        }
    }
    $rows = query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
            $positions[] = [
                "name" => "Cash",
                "price" => $rows[0]["cash"],
                "shares" => "",
                "symbol" => ""
            ];
    render("portfolio.php", ["title" => "Portfolio", "positions" => $positions]);
?>
