<table>
    <tr>
        <th>Name</th>
        <th>Symbol</th>
        <th>Shares</th>
        <th>Price</th>
        <th>Value</th>
    </tr>
    <br/>

    <?php foreach ($positions as $position): ?>

        <tr>
            <td><?= $position["name"] ?></td>
            <td><?= $position["symbol"] ?></td>
            <td><?= $position["shares"] ?></td>
            <td><?= number_format($position["price"], 2) ?></td>

            <td><?= number_format(is_null ($position["shares"]) ? $position["shares"] : 1 * $position["price"], 2) ?></td>
        </tr>
        <br/>

    <?php endforeach ?>
</table>

<!--
<div>
    <img alt="Under Construction" src="/img/construction.gif"/>
</div>
<div>
    <a href="logout.php">Log Out</a>
</div>
-->
