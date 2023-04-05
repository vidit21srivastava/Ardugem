const express = require("express")
const axios = require('axios')
const app = express()

app.get(`/api/statistics`, async (req, res) => {
    let symbol = req.query["symbol"]
    try {
        let { data } = await axios.get(`https://api.binance.com/api/v3/ticker/24hr?symbol=${symbol}`)
        console.log(data);
        res.send(`${data.lastPrice}&${data.priceChangePercent}`).status(200);
        return;
    } catch (error) {
       console.log(error) 
    }
})

app.listen(3001)