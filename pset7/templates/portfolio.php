                <table>
                    <tr>
                        <th>Name</th>
                        <th>Symbol</th>
                        <th>Shares</th>
                        <th>Price</th>
                        <th>Value</th>
                    </tr>
                <?php foreach ($positions as $position): ?>
                    <tr>
                        <td><?= $position["name"] ?></td>
                        <td><?= $position["symbol"] ?></td>
                        <td class=number><?= $position["shares"] ?></td>
                        <td class=number>$<?= number_format($position["price"], $position["name"] == "Cash" ? 2 : 4) ?></td>
                        <td class=number>$<?= number_format(($position["shares"] == "" ? 1 : $position["shares"]) * $position["price"], 2) ?></td>
                    </tr>
                <?php endforeach ?>
</table>
