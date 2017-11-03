var TemporaryGuess;
var Size;
var NumberToBeGuessed;
var TriesSoFar = 1;

function genRand() {
    var number = []; 
    var temp;
    do {
        temp = Math.floor(Math.random() * 10);
    } while (temp == 0);
    number.push(temp);
    for (var i = 1; i < Size; i++) {
        do {
            temp = Math.floor(Math.random() * 10);
        } while (number.indexOf(temp) >= 0);
        number.push(temp);
    }
    return number;
}

$(document).ready(function() {
    $(".toSuggest").hide();
    $("#NG").click(function() {
        Size = $("#numLen").val();
        NumberToBeGuessed = genRand();
        $("#NG").hide();
        $("#numLen").hide();
        $("#numLenVal").hide();
        $(".toSuggest").show();
    });
});

function checkIfArrayIsUnique(myArray) {
    return myArray.length === new Set(myArray).size;
}

$("#submitNum").click(function() {
    TemporaryGuess = $("#suggNum").val().toString(10).split("").map(function(t){return parseInt(t)});
    var IsNumericString = TemporaryGuess;

    if (IsNumericString.filter(function(i){ return isNaN(i); }).length > 0) {
        alert("Enter numbers only");
        TemporaryGuess = 0;
    } else if (!checkIfArrayIsUnique(TemporaryGuess)) {
        alert("Enter non duplicating digits");
        TemporaryGuess = 0;
    } else if ($("#suggNum").val().length != Size) {
        alert("Enter number with valid size");
        TemporaryGuess = 0;
    } else if (TemporaryGuess[0] == 0) {
        alert("Enter number beginning with a non-zero digit");
        TemporaryGuess = 0;
    } else {
        var obj = checkBullsAndCows(TemporaryGuess.join(','));
        if ($("#suggNum").val() == convertArrayToNumber(NumberToBeGuessed)) {
            $("#one").append("<p>Ход " + TriesSoFar + ": " + convertArrayToNumber(TemporaryGuess) +
             ": решение</p>");
        } else {
            $("#one").append("<p>Ход " + TriesSoFar + ": " + convertArrayToNumber(TemporaryGuess) + 
                " : " + obj[0] + " б. " + obj[1] + " к. <br></p>");
            TriesSoFar += 1;
        }
    }
    $("#suggNum").val("");
});

$("#suggNum").keyup(function(event) {
    if (event.keyCode == 13) {
        $("#submitNum").click();
    }
});

function convertArrayToNumber(arg) {
    return parseInt(arg.join(""));
}

function convertStringToArray(arg) {
    return arg.split(',').map(function(n) {
        return parseInt(n);
    });
}

function checkBullsAndCows(val) {
    var bulls = 0, cows = 0;
    var array = val.split(',');
    array.forEach(function(val, index) {
        if ($.inArray(parseInt(val), NumberToBeGuessed) >= 0) {
            if ($.inArray(parseInt(val), NumberToBeGuessed) == index) {
                bulls += 1;
            } else {
                cows += 1;
            }
        }
    });
    return [ bulls, cows ];
}

function checkCurrentSolution() {
    var obj = checkBullsAndCows(TemporaryGuess.join(','));
    return " " + obj[0] + (obj[0] == 1 ? " бик " : " бика ") +
        obj[1] + (obj[1] == 1 ? " крава" : " крави");
}

$("#displayCurrentSolution").click(function() {
    $("#one").append("<p>" + checkCurrentSolution() + "<br></p>");
});

$("#surrender").click(function() {
    $("#one").text(convertArrayToNumber(NumberToBeGuessed));
});

$("#restart").click(function() {
    TriesSoFar = 1;
    $("#one").text("");    
});
