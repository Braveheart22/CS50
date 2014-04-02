<p>
    You have sold <?= htmlspecialchars($stockToSell["shares"]) ?> shares of <?= htmlspecialchars($stockToSell["symbol"]) ?> for <strong>$<?= (htmlspecialchars (number_format ($stockToSell["price"], 2))) ?></strong> a share.
</p>

