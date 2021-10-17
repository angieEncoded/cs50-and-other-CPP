window.addEventListener("load", function() {


    // QUESTION 1
    // ======================================

    // Helper functions to deal with responses
    const responseLogic = (event) => {
        // Get the target button
        const element = event.target;

        // Clear all colors from buttons
        const buttons = document.querySelectorAll(".triv1");
        buttons.forEach(button => {
            button.classList.remove("incorrect")
            button.classList.remove("correct")
        })

        // Correct answer
        if (element.innerHTML == "1987") {
            element.classList.add("correct")
            feedback.innerHTML = "That is the correct response!"
            feedback.className = "correct-text"
            // incorrect answer
        }
        else {
            element.classList.add("incorrect")
            feedback.className = "incorrect-text"
            feedback.innerHTML = "That is not the correct response."
        }
        // console.log(event.target.innerHTML)
    }

    // Feedback container and a loop to add a listener to all buttons
    const feedback = document.querySelector("#feedback");
    document.querySelectorAll(".triv1").forEach(button => {
        button.addEventListener("click", responseLogic)
    })

    // END QUESTION 1
    // ======================================


    // QUESTION 2
    // ======================================

    const handleData = (event) => {

        const response = input.value;
        if (response.includes("7")) {
            feedback2.innerHTML = "Lol no."
            feedback2.classList.add("incorrect-text")
            feedback2.classList.remove("correct-text")
            feedback2.classList.remove("warning-text")
            return;
        }

        if (response.includes("9")) {
            feedback2.innerHTML = "I agree! Hands down, that was the best."
            feedback2.classList.add("correct-text")
            feedback2.classList.remove("incorrect-text")
            feedback2.classList.remove("warning-text")
            return;
        }

        feedback2.innerHTML = "Yea that one was okay. Not the BEST, though."
        feedback2.classList.remove("correct-text")
        feedback2.classList.remove("incorrect-text")
        feedback2.classList.add("warning-text")

    }

    const input = document.querySelector("#favResponse");
    const feedback2 = document.querySelector(".feedback2");
    const confirm = this.document.querySelector("#confirm");
    confirm.addEventListener("click", handleData);




    // END QUESTION 2
    // ======================================







});
