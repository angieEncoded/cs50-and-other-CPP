
/*

Card must be either 13,15,or 16 digits
Card must not have any alpha characters
amex starts with 36 or 37
mastercard starts with 51,52,53,54,55
visa starts with 4

Checksum formula : Luhn's algorithm
Start at the next to last digit and multiply every other digit by two
Add the products together
Sooooo x[pos] * 2 + x[pos - 2] + x[pos - 2]...
Store that sum in a variable
Then add the other digits together (without any manipulation) and then add that to the "doubles" sum
If the last digit is a zero, we're good (totalSum modulo 10 should be 0)

other thoughts
Can I do this in one loop? if I use modulo to determine if i is even, maybe.

*/




const dummyVisa = 4012888888881881;
const dummyMasterCard = 2221000000000009;
const dummyAmexCard = 378282246310005;

const determineCard = (cardNumber) =>{
    let cardType;
    for(let item of cardNumber){
        // If it's a visa we can jump right out
        if (item === "4")
        {
         cardType = "VISA";
         break;
        } else if (item === "3"){

        }
    }

}

console.log(determineCard(dummyVisa));

