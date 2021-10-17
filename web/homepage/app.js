// pick a random quote from the array and insert it into the html. 
// I started using the fetch api
// to get one from a server but ran into the client side cors issue 
// and didn't want it to carry over into the submission. Plus I was 
// starting to spend too much time in this project and it's getting 
// converted to a React App as soon as it's submitted anyway. 


// When we are done loading
window.addEventListener("load", function () {
    // Get the toast container
    const toastLocation = document.querySelector("#toast-loc");

    // set up some dummy data
    const catQuotes = [
        { "name": "Sasha", "quote": "I never met a desk I didn't like." },
        { "name": "Shakey", "quote": "Get dat bacon!" },
        { "name": "Shuttle", "quote": "Why doesn't babs love me?" },
        { "name": "Rory", "quote": "Why did you bring these kittens here?" },
        { "name": "Babs", "quote": "Shuttle really needs to stop following me around." },
        { "name": "Babs", "quote": "What do you think I am, an exterminator?" },
        { "name": "Yaya", "quote": "This keyboard is mine." },
        { "name": "Calico", "quote": "Remember that frog I ate half of?" },
        { "name": "Sasha", "quote": "Is it dinnertime yet?" },
        { "name": "Shuttle", "quote": "Tuxedo Therapy Services, LLC is always there for you." },
    ]

    // set up the function that will build and show the toast
    const getQuote = () => {

        // get the current time
        const time = new Date().toLocaleTimeString()

        // get pseudo random number - good enough for this project
        const quote = catQuotes[Math.floor(Math.random() * catQuotes.length)];
        console.log(quote)

        // construct the html that will be returned for the toast
        const toastText =
            `
            <div class="position-fixed bottom-0 end-0 p-3" style="z-index: 11">
                <div id="catQuoteToast" class="toast" role="alert" aria-live="assertive" aria-atomic="true" data-bs-delay="10000">
                    <div class="toast-header">
                        <strong class="me-auto">${quote.name}</strong>
                        <small>${time}</small>
                        <button type="button" class="btn-close" data-bs-dismiss="toast" aria-label="Close"></button>
                    </div>
                    <div class="toast-body">
                        ${quote.quote}
                    </div>
                </div>
              </div>

            `

        // Insert the toast into the html
        toastLocation.innerHTML = toastText

        // Activate the toast with bootstrap (from docs)
        const catQuoteToast = document.getElementById('catQuoteToast')
        const toast = new bootstrap.Toast(catQuoteToast)


        // show the toast - added data-bs-delay="3000" to the markup to change bootstrap's timeout
        toast.show()


    }

    // set up a function that will manage the toasts
    const showQuotes = () => {
        // get a quote 5 seconds after loading the page
        setTimeout(getQuote, 5000);

        // set up an interval to get a quote every 30 seconds thereafter
        setInterval(getQuote, 30000);
    }

    // call the function
    showQuotes();

})