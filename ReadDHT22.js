/**
 * Created by tom on 01.04.17.
 */
const request = require('request');

//Set IP and PORT
const ip = '192.168.2.23';
const port = 1337;

//GET ESP's Page
request(`http://${ip}:${port}`, (err, response, body) => {

    //Check for Errors (like timeout)
    if (err) throw err;

    //Check for HTTP Response Code
    switch (response.statusCode) {
        //Everything fine
        case 200:
            const jsonbody = JSON.parse(body);
            console.log(`We have ${jsonbody.temperature} Degrees and a humidity of ${jsonbody.humidity}%`);
            break;
        //Damn - 500. ESP sends 500 when the ESP read fails
        case 500:
            console.error('The ESP returned 500. This could happen when the ESP isnt connected correctly');
            break;
        //Any other error code
        default:
            console.error(`There was an error while reading out the ESP. HTTP Status Code was ${response.statusCode}`);
    }
});