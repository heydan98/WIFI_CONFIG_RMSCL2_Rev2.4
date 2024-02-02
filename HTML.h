const char htmlContent[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
  <head>
    <title>Data validation interface</title>
    <meta name="viewport" content="width=device-width, initial-scale=1" />
    <style>
      body {
        font-family: Roboto, sans-serif;
      }
      .container {
        width: 95%;
        max-width: 450px;
        margin: 0 auto;
        padding: 30px;
        border: 2px solid #2e1212;
        border-radius: 30px;
        background-color: #3093e4;
        overflow: auto;
        display: flex;
        flex-direction: column;
        align-items: stretch;
      }
      .header {
        text-align: center;
      }
      .frame {
        flex: 1;
        margin-bottom: 20px;
        display: flex;
        flex-direction: column;
      }
      .table {
        width: 100%;
        border-collapse: collapse;
      }
      .table th,
      .table td {
        padding: 10px;
        text-align: left;
        border: 1px solid #1279c8;
        background-color: #b6e4f4;
      }
      .table th {
        text-align: center;
      }

      .table .header-row th {
        background-color: skyblue;
      }
      .button {
        text-align: center;
      }
      .button button {
        padding: 10px 20px;
        font-size: 16px;
        background-color: #33bee9;
        color: #ff0000;
        border: none;
        border-radius: 7px;
        cursor: pointer;
      }
      .button button:hover {
        background-color: #0e8ac0;
      }

      .right-column {
        text-align: center;
        flex: 1;
      }
      .left-column {
        text-align: center;
      }
      .right-column input[type="text"] {
        width: 100%;
        box-sizing: border-box;
      }
      .right-column select {
        width: 100%;
        padding: 8px;
        border: 10px solid #f40d0d;
        border-radius: 5px;
        box-sizing: border-box;
      }
      .column-container {
        display: flex;
        flex-wrap: wrap;
      }
      .column-container .column {
        flex: 1;
      }
      .hidden {
        display: none;
      }
      .data-send-container {
        display: flex;
        flex-direction: column;
        align-items: center;
        text-align: center;
      }
      .data-send-container input[type="text"] {
        max-width: 100px;
        box-sizing: border-box;
      }
      .hidden-row {
        display: none;
      }
      .button-container {
        display: flex;
        align-items: center;
        justify-content: space-between;
      }
      .button-container button {
        font-size: 18px;
        background-color: #4caf50;
        color: #020010;
        border: none;
        border-radius: 5px;
        cursor: pointer;
        padding: 5px 10px;
      }
      .button-container button:hover {
        background-color: #45a049;
      }
      .centered {
        margin: 0 auto;
      }
      #rs485Options {
        margin: 0 auto;
        display: block;
      }
      .analog-inputs {
        display: none;
      }

      .show-analog-inputs .analog-inputs {
        display: table-cell;
      }
      .input-half-width {
        width: calc(50% - 1px); 
        margin: 0;
      }
      .digital-inputs,
      .customize-inputs {
        display: none;
      }
      .show-digital-inputs .digital-inputs,
      .show-customize-inputs .customize-inputs {
        display: table-cell;
      }
      .input-small {
        width: 40px; 
      }
    </style>
    <script>
      
      function formatValue(inputField) {
        const inputValue = inputField.value;

        // Insert a space after every two characters, except at the beginning
        inputField.value = inputValue.replace(/(\d{2})(?=\d)/g, '$1 ');
      }
      function toggleMode() {
        var modeSelect = document.getElementById("modeSelect");
        var wifiSettings = document.querySelectorAll(".hidden#wifiSettings");
        var sim4GSettings = document.querySelectorAll(".hidden#sim4GSettings");
        var lorawanSettings = document.querySelectorAll(".hidden#lorawanSettings");

        if (modeSelect.value === "WIFI") {
          wifiSettings.forEach((element) => {
            element.style.display = "table-row";
          });
          sim4GSettings.forEach((element) => {
            element.style.display = "none";
          });
          lorawanSettings.forEach((element) => {
            element.style.display = "none";
          });
          var otaaSettings = document.querySelectorAll(".hidden#otaaSettings");
          var abpSettings = document.querySelectorAll(".hidden#abpSettings");
          otaaSettings.forEach((element) => {
            element.style.display = "none";
          });
          abpSettings.forEach((element) => {
            element.style.display = "none";
          });
        } else if (modeSelect.value === "SIM4G") {
          wifiSettings.forEach((element) => {
            element.style.display = "none";
          });
          sim4GSettings.forEach((element) => {
            element.style.display = "table-row";
          });
          lorawanSettings.forEach((element) => {
            element.style.display = "none";
          });
          var otaaSettings = document.querySelectorAll(".hidden#otaaSettings");
          var abpSettings = document.querySelectorAll(".hidden#abpSettings");
          otaaSettings.forEach((element) => {
            element.style.display = "none";
          });
          abpSettings.forEach((element) => {
            element.style.display = "none";
          });
        } else if (modeSelect.value === "LORAWAN"){
          wifiSettings.forEach((element) => {
            element.style.display = "none";
          });
          sim4GSettings.forEach((element) => {
            element.style.display = "none";
          });
          lorawanSettings.forEach((element) => {
            element.style.display = "table-row";
          });
        }
        else {
          wifiSettings.forEach((element) => {
            element.style.display = "none";
          });
          sim4GSettings.forEach((element) => {
            element.style.display = "none";
          });
          lorawanSettings.forEach((element) => {
            element.style.display = "none";
          });
        }
      }

      function toggleModeLora() {
        var modeLoraSelect = document.getElementById("modeLoraSelect");
        
        var otaaSettings = document.querySelectorAll(".hidden#otaaSettings");
        var abpSettings = document.querySelectorAll(".hidden#abpSettings");

        if (modeLoraSelect.value === "OTAA") {
          otaaSettings.forEach((element) => {
            element.style.display = "table-row";
          });
          abpSettings.forEach((element) => {
            element.style.display = "none";
          });
        } else if (modeLoraSelect.value === "ABP") {
          otaaSettings.forEach((element) => {
            element.style.display = "none";
          });
          abpSettings.forEach((element) => {
            element.style.display = "table-row";
          });
        } else {
          otaaSettings.forEach((element) => {
            element.style.display = "none";
          });
          abpSettings.forEach((element) => {
            element.style.display = "none";
          });
        }
      }

      function toggleClassLora() {
        var classSelectOTAA = document.getElementById("classSelectOTAA");
        var classSelectABP = document.getElementById("classSelectABP");
        var abpClassSettings = document.querySelectorAll(".hidden#abpSettings");
        var classSettings = document.querySelectorAll(".hidden#otaaSettings");

        // if (classSelect.value === "A" || classSelect.value === "C") {
        //   abpClassSettings.forEach((element) => {
        //     element.style.display = "none";
        //   });
        //   classSettings.forEach((element) => {
        //     element.style.display = "table-row";
        //   });
        // } else {
        //   abpClassSettings.forEach((element) => {
        //     element.style.display = "table-row";
        //   });
        //   classSettings.forEach((element) => {
        //     element.style.display = "none";
        //   });
        // }
      }
      function checkmodeSelect() {
        var modeSelect = document.getElementById("modeSelect").value;
        if (modeSelect === "WIFI") {
          document
            .getElementById("modeSelect")
            .setAttribute("data-type", "WIFI");
        } else if (modeSelect === "SIM4G") {
          document
            .getElementById("modeSelect")
            .setAttribute("data-type", "SIM4G");
        } else if (modeSelect === "LORAWAN") {
          document
            .getElementById("modeSelect")
            .setAttribute("data-type", "LORAWAN");
        }
      }

      function checkmodeLoraSelect() {
        var modeLoraSelect = document.getElementById("modeLoraSelect").value;

        if (modeLoraSelect === "OTAA") {
          document
            .getElementById("modeLoraSelect")
            .setAttribute("data-type", "OTAA");
        } else {
          document
            .getElementById("modeLoraSelect")
            .setAttribute("data-type", "ABP");
        }
      }

      function checkclassLoraSelect() {
        var classSelectOTAA = document.getElementById("classSelectOTAA").value;
        var classSelectABP = document.getElementById("classSelectABP").value;

        if (classSelectOTAA === "A") {
          document.getElementById("classSelectOTAA").setAttribute("data-type", "A");
        } else {
          document.getElementById("classSelectOTAA").setAttribute("data-type", "C");
        }
        
        if (classSelectABP === "A") {
          document.getElementById("classSelectABP").setAttribute("data-type", "A");
        } else {
          document.getElementById("classSelectABP").setAttribute("data-type", "C");
        }
      }

      function toggleRS485Settings() {
        var rs485Options = document.getElementById("rs485Options").value;
        var tempHumSettings = document.querySelectorAll(".tempHumSettings");
        var phSettings = document.querySelectorAll(".phSettings");
        var customSettings = document.querySelectorAll(".customSettings");

        if (rs485Options === "Temp/Hum") {
          tempHumSettings.forEach((element) => {
            element.style.display = "table-row";
          });
          phSettings.forEach((element) => {
            element.style.display = "none";
          });
          customSettings.forEach((element) => {
            element.style.display = "none";
          });
        } else if (rs485Options === "PH") {
          tempHumSettings.forEach((element) => {
            element.style.display = "none";
          });
          phSettings.forEach((element) => {
            element.style.display = "table-row";
          });
          customSettings.forEach((element) => {
            element.style.display = "none";
          });
        } else if (rs485Options === "custom") {
          customSettings.forEach((element) => {
            element.style.display = "table-row";
          });
          tempHumSettings.forEach((element) => {
            element.style.display = "none";
          });
          phSettings.forEach((element) => {
            element.style.display = "none";
          });
        } else {
          tempHumSettings.forEach((element) => {
            element.style.display = "none";
          });
          phSettings.forEach((element) => {
            element.style.display = "none";
          });
          customSettings.forEach((element) => {
            element.style.display = "none";
          });
        }
      }

      function toggleRS485Data() {
        var rs485Options = document.getElementById("rs485Options").value;
        var tempHumSettings = document.querySelectorAll(".tempHumSettings");
        var phSettings = document.querySelectorAll(".phSettings");
        var customSettings = document.querySelectorAll(".customSettings");

        if (rs485Options === "Temp/Hum") {
          tempHumSettings.forEach((element) => {
            element.style.display = "table-row";
          });
          phSettings.forEach((element) => {
            element.style.display = "none";
          });
          customSettings.forEach((element) => {
            element.style.display = "none";
          });
        } else if (rs485Options === "PH") {
          tempHumSettings.forEach((element) => {
            element.style.display = "none";
          });
          phSettings.forEach((element) => {
            element.style.display = "table-row";
          });
          customSettings.forEach((element) => {
            element.style.display = "none";
          });
        } else if (rs485Options === "custom") {
          customSettings.forEach((element) => {
            element.style.display = "table-row";
          });
          tempHumSettings.forEach((element) => {
            element.style.display = "none";
          });
          phSettings.forEach((element) => {
            element.style.display = "none";
          });
        } else {
          tempHumSettings.forEach((element) => {
            element.style.display = "none";
          });
          phSettings.forEach((element) => {
            element.style.display = "none";
          });
          customSettings.forEach((element) => {
            element.style.display = "none";
          });
        }
      }

      function toggleDataType(selectElement) {
        var dataRow = selectElement.closest(".data-row");
        var dataInputs = dataRow.querySelectorAll(".data-inputs");
        var dataType = selectElement.value;

        dataInputs.forEach(function (input) {
          input.style.display = "none";
        });

        if (dataType === "Analog") {
          var analogInputs = dataRow.querySelectorAll(".analog-inputs");
          analogInputs.forEach(function (input) {
            input.style.display = "table-cell";
          });
        } else if (dataType === "Digital" || dataType === "Customize") {
          var digitalInputs = dataRow.querySelectorAll(".digital-inputs");
          digitalInputs.forEach(function (input) {
            input.style.display = "table-cell";
          });
        }

        // Concatenate values if the selected type is Analog
        if (dataType === "Analog") {
          dataRow.querySelector(".digital-inputs #value13").value =
            dataRow.querySelector(".analog-inputs #value30").value +
            "," +
            dataRow.querySelector(".analog-inputs #value31").value;

          dataRow.querySelector(".digital-inputs #value15").value =
            dataRow.querySelector(".analog-inputs #value32").value +
            "," +
            dataRow.querySelector(".analog-inputs #value33").value;

          dataRow.querySelector(".digital-inputs #value17").value =
            dataRow.querySelector(".analog-inputs #value34").value +
            "," +
            dataRow.querySelector(".analog-inputs #value35").value;

          dataRow.querySelector(".digital-inputs #value19").value =
            dataRow.querySelector(".analog-inputs #value36").value +
            "," +
            dataRow.querySelector(".analog-inputs #value37").value;

          dataRow.querySelector(".digital-inputs #value21").value =
            dataRow.querySelector(".analog-inputs #value38").value +
            "," +
            dataRow.querySelector(".analog-inputs #value39").value;
        }
      }

      function toggleDataRows() {
        var dataRows = document.querySelectorAll(".data-row");

        if (dataRowCount < 5) {
          dataRowCount++;
          dataRows[dataRowCount - 1].style.display = "table-row";
        }

        var addButton = document.querySelector(".add-button");
        var removeButton = document.querySelector(".remove-button");

        addButton.disabled = dataRowCount >= 5;
        removeButton.disabled = dataRowCount <= 0;
      }

      function addDataRow(button) {
        var hiddenRow = document.querySelector(".hidden-row");
        if (hiddenRow) {
          hiddenRow.classList.remove("hidden-row");
          dataRowCount++;
        }

        var addButton = document.querySelector(".add-button");
        addButton.disabled = dataRowCount >= 5;

        var removeButton = document.querySelector(".remove-button");
        removeButton.disabled = dataRowCount <= 0;
      }

      function removeDataRow(button) {
        var row = button.parentNode.parentNode;
        row.style.display = "none";
        dataRowCount--;

        var addButton = document.querySelector(".add-button");
        addButton.disabled = dataRowCount >= 5;

        var removeButton = document.querySelector(".remove-button");
        removeButton.disabled = dataRowCount <= 0;
      }

      document.addEventListener("DOMContentLoaded", function () {
        var addButton = document.querySelector(".add-button");
        var removeButton = document.querySelector(".remove-button");

        // Initialize dataRowCount based on the initial number of visible data rows
        dataRowCount = document.querySelectorAll(
          ".data-row:not(.hidden-row)"
        ).length;

        addButton.disabled = dataRowCount >= 5;
        removeButton.disabled = dataRowCount <= 0;

        var addDataButtons = document.querySelectorAll(".add-data-button");
        addDataButtons.forEach(function (button) {
          button.addEventListener("click", function () {
            addDataRow(button);
          });
        });
      });

      function sendValues() {
        var dataType;
        var value1 = document.getElementById("value1").value;
        var value2 = document.getElementById("value2").value;
        var value3 = document.getElementById("value3").value;
        var value4 = document.getElementById("value4").value;
        var value5 = document.getElementById("value5").value;
        var value6 = document.getElementById("value6").value;
        var value7 = document.getElementById("value7").value;
        var value8 = document.getElementById("value8").value;
        var value9 = document.getElementById("value9").value;
        var value10 = document.getElementById("value10").value;
        var value11 = document.getElementById("value11").value;
        var value12 = document.getElementById("value12").value;
        var value14 = document.getElementById("value14").value;
        var value16 = document.getElementById("value16").value;
        var value18 = document.getElementById("value18").value;
        var value20 = document.getElementById("value20").value;
        var value22 = document.getElementById("value22").value;
        var value23 = document.getElementById("value23").value;
        // var value24 = document.getElementById("value24").value;
        // var value25 = document.getElementById("value25").value;



        var dataType1 = document.getElementById("dataType1").value;
        var dataType2 = document.getElementById("dataType2").value;
        var dataType3 = document.getElementById("dataType3").value;
        var dataType4 = document.getElementById("dataType4").value;
        var dataType5 = document.getElementById("dataType5").value;

        if (dataType1 === "Analog") {
          var value30 = document.getElementById("value30").value;
          var value31 = document.getElementById("value31").value;
          var value13 = [value30, value31];
        }else {
          var value13 = document.getElementById("value13").value;
        }
        if (dataType2 === "Analog" ){
          var value32 = document.getElementById("value32").value;
          var value33 = document.getElementById("value33").value;
          var value15 = [value32, value33];
        }else {
          var value15 = document.getElementById("value15").value;
        }
        if (dataType3 === "Analog"){
          var value34 = document.getElementById("value34").value;
          var value35 = document.getElementById("value35").value;
          var value17 = [value34, value35];
        }else {
          var value17 = document.getElementById("value17").value;
        }
        if (dataType4 === "Analog"){
          var value36 = document.getElementById("value36").value;
          var value37 = document.getElementById("value37").value;
          var value19 = [value36, value37];
        }else {
          var value19 = document.getElementById("value19").value;
        }
        if (dataType5 === "Analog"){
          var value38 = document.getElementById("value38").value;
          var value39 = document.getElementById("value39").value;
          var value21 = [value38, value39];
      }else {
          var value21 = document.getElementById("value21").value;
        }

        var tempInput = document.getElementById("tempInput").value;
        var humInput = document.getElementById("humInput").value;
        var customInput1 = document.getElementById("customInput1").value;
        var ByteSelect1 = document.getElementById("ByteSelect1").value;
        var ByteSelect2 = document.getElementById("ByteSelect2").value;
        var customInput2 = [ByteSelect1, ByteSelect2];
        var customInput3 = document.getElementById("customInput3").value;
        var ByteSelect3 = document.getElementById("ByteSelect3").value;
        var ByteSelect4 = document.getElementById("ByteSelect4").value;
        var customInput4 = [ByteSelect3, ByteSelect4];
        var modeSelect = document.getElementById("modeSelect").value;


        var modeLoraSelect = document.getElementById("modeLoraSelect").value;
        var classSelectOTAA = document.getElementById("classSelectOTAA").value;
        var classSelectABP = document.getElementById("classSelectABP").value;
        var rs485Options = document.getElementById("rs485Options").value;
        
        var xhr = new XMLHttpRequest();
        xhr.open("POST", "/process", true);
        xhr.setRequestHeader(
          "Content-Type",
          "application/x-www-form-urlencoded"
        );
        xhr.onreadystatechange = function () {
          if (xhr.readyState === 4 && xhr.status === 200) {
            var successMessage = document.createElement("div");
            successMessage.className = "success-message";
            successMessage.style.cssText = "width: 300px; height: auto; padding: 20px; border: 1px solid #ccc; border-radius: 10px; background-color: #3498db; box-shadow: 0px 0px 10px rgba(0, 0, 0, 0.3); position: fixed; top: 50%; left: 50%; transform: translate(-50%, -50%); display: flex; flex-direction: column; align-items: center; justify-content: center;";
            
            var successText = document.createElement("div");
            successText.innerHTML = "Send success";
            successText.style.cssText = "color: #fff; margin-bottom: 20px; text-align: center; font-weight: bold; font-size: 24px;";
            
            var okButton = document.createElement("button");
            okButton.innerHTML = "OK";
            okButton.style.cssText = "background-color: #2ecc71; border: none; border-radius: 5px; padding: 10px 20px; color: #fff; cursor: pointer; font-size: 18px;";
            okButton.onclick = function () {
              countdown();
              successMessage.style.display = "none";
            };
            
            successMessage.appendChild(successText);
            successMessage.appendChild(okButton);
            document.body.appendChild(successMessage);}
        };
        xhr.send(
          "value1=" + encodeURIComponent(value1) +
            "&value2=" + encodeURIComponent(value2) +
            "&value3=" + encodeURIComponent(value3) +
            "&value4=" + encodeURIComponent(value4) +
            "&value5=" + encodeURIComponent(value5) +
            "&value6=" + encodeURIComponent(value6) +
            "&value7=" + encodeURIComponent(value7) +
            "&value8=" + encodeURIComponent(value8) +
            "&value9=" + encodeURIComponent(value9) +
            "&value10=" + encodeURIComponent(value10) +
            "&value11=" + encodeURIComponent(value11) +
            "&value12=" + encodeURIComponent(value12) +
            "&value13=" + encodeURIComponent(value13) +
            "&value14=" + encodeURIComponent(value14) +
            "&value17=" + encodeURIComponent(value17) +
            "&value15=" + encodeURIComponent(value15) +
            "&value16=" + encodeURIComponent(value16) +
            "&value18=" + encodeURIComponent(value18) +
            "&value19=" + encodeURIComponent(value19) +
            "&value20=" + encodeURIComponent(value20) +
            "&value22=" + encodeURIComponent(value22) +
            "&value23=" + encodeURIComponent(value23) +
            // "&value24=" + encodeURIComponent(value24) +
            // "&value25=" + encodeURIComponent(value25) +


            "&tempInput=" + encodeURIComponent(tempInput) +
            "&humInput=" + encodeURIComponent(humInput) +
            "&customInput1=" + encodeURIComponent(customInput1) +
            "&customInput2=" + encodeURIComponent(customInput2) +
            "&customInput3=" + encodeURIComponent(customInput3) +
            "&customInput4=" + encodeURIComponent(customInput4) +
            "&value21=" + encodeURIComponent(value21) +
            "&modeSelect=" + encodeURIComponent(modeSelect) +
            "&modeLoraSelect=" + encodeURIComponent(modeLoraSelect) +
            "&classSelectOTAA=" + encodeURIComponent(classSelectOTAA) +
            "&classSelectABP=" + encodeURIComponent(classSelectABP) +
            "&rs485Options=" + encodeURIComponent(rs485Options) +
            "&dataType1=" + encodeURIComponent(dataType1) +
            "&dataType2=" + encodeURIComponent(dataType2) +
            "&dataType3=" + encodeURIComponent(dataType3) +
            "&dataType4=" + encodeURIComponent(dataType4) +
            "&dataType5=" + encodeURIComponent(dataType5)
        );
      }

      function countdown() {
        var count = 5;
        var countdownMessage = document.createElement("div");
        countdownMessage.style.cssText = "position:fixed;top:50%;left:50%;transform:translate(-50%,-50%);fontSize:18px;";
        countdownMessage.innerHTML = "Page will close in " + count + "s...";
      
        document.querySelector(".container").appendChild(countdownMessage);
      
        var countdownInterval = setInterval(function () {
          if (--count <= 0) {
            clearInterval(countdownInterval);
            window.location.href = "/thankyou.html";
          } else {
            countdownMessage.innerHTML = "Page will close in " + count + "s...";
          }
        }, 1000);
      }
    </script>
  </head>
  <body>
    <div class="container">
      <div class="frame">
        <!-- <div class="header" style="position: fixed; top: 1; width: 30%; z-index: 5;"> -->
        <div class="header">
          <!-- <h2 style="text-align: center">TMA Innovation</h2> -->
          <!-- <img src="TMALogo.svg" alt="TMA Innovation"> -->
          <svg width="134" height="58" viewBox="0 0 134 58" fill="none" xmlns="http://www.w3.org/2000/svg">
          <g clip-path="url(#clip0_72_2474)">
          <g clip-path="url(#clip1_72_2474)">
          <path fill-rule="evenodd" clip-rule="evenodd" d="M85.2485 2.86127L70.0361 37.6898C69.8386 38.7751 69.9374 39.3671 70.0361 39.9591L77.4448 38.1831C78.4326 31.9673 86.1375 27.7247 93.2498 26.0474L95.423 31.6713L102.041 30.6846L99.6706 25.2581C104.807 24.7648 112.117 24.7648 121.995 32.5593C131.972 40.3537 134.343 57.916 133.849 56.0414C133.355 54.1668 134.145 41.1431 125.453 31.4739C117.748 23.4821 110.24 20.2262 97.3986 20.7195L89.4961 1.3813L85.2485 2.86127ZM33.6845 2.86127L27.0662 36.3085L32.8943 39.1698L37.9321 16.2796L47.5139 39.9591L51.0701 36.9991L57.6884 16.8716L62.3312 39.9591L68.6532 36.9005L62.1336 0L55.9104 2.95993L48.2054 24.9621L39.3151 0.789315L33.6845 2.86127ZM0 7.89315L2.76588 1.3813C11.3599 1.3813 19.7563 1.3813 28.3503 1.3813L25.5844 7.89315H17.4843V37.1965H10.3721V7.89315H0ZM91.7681 21.5088C91.9656 21.1142 82.5814 24.5674 82.5814 25.4554L87.8168 13.0237L91.7681 21.5088Z" fill="white"/>
          <path fill-rule="evenodd" clip-rule="evenodd" d="M100.564 29.6982C108.17 29.6982 114.294 35.914 114.294 43.7085C114.294 51.4043 108.17 57.7189 100.564 57.7189C92.9575 57.7189 86.833 51.503 86.833 43.7085C86.9318 36.0127 93.0562 29.6982 100.564 29.6982Z" fill="#A8A9AD"/>
          <path fill-rule="evenodd" clip-rule="evenodd" d="M86.829 42.9229C88.6071 42.6269 90.1876 41.0482 87.6193 40.5549C87.1254 40.4563 87.5205 39.5683 87.8169 39.5683C89.0022 39.4696 92.6572 41.9362 92.6572 43.5148C92.6572 48.8427 94.534 47.4614 96.3121 44.8962C98.3865 42.0349 99.4731 45.4881 100.658 47.8561C100.955 48.4481 103.424 49.2374 103.424 48.2507C103.424 47.1654 103.128 46.0801 102.338 45.2908C102.338 45.2908 105.499 44.5015 105.993 43.5148C106.882 41.6402 105.202 35.6217 107.474 40.3576C107.968 41.3442 108.561 41.1469 108.759 40.5549C108.857 40.1603 108.66 39.4696 108.759 39.2723C109.252 36.3123 112.117 39.4696 109.055 34.9311C107.474 32.6618 110.142 33.3524 110.537 34.1417C111.129 35.227 109.252 31.9711 104.807 30.3925C98.8804 28.3205 91.8669 31.2805 88.9035 36.6083C86.6315 40.7522 86.829 42.1335 86.829 42.9229ZM98.7816 49.7307C99.078 49.8294 99.2755 50.1254 99.5719 50.4214C99.7694 50.7173 100.263 51.2107 100.56 51.408C100.955 51.8027 101.35 52.4933 101.35 53.0853C101.35 53.184 101.449 53.5786 101.251 53.5786C101.152 53.5786 101.054 53.4799 101.054 53.4799C100.955 53.4799 100.856 53.4799 100.856 53.3813C100.757 53.2826 100.658 53.184 100.658 52.9866L100.56 52.592C100.461 52.4933 100.362 52.1973 100.362 52C100.263 51.6053 99.8682 51.112 99.7694 50.816C99.4731 50.6187 98.7816 49.928 98.7816 49.7307ZM99.8682 47.5601C99.8682 47.9547 99.8682 48.3494 99.8682 48.7441C99.8682 48.8427 99.967 49.2374 99.967 49.2374L100.066 49.4347C100.165 49.5334 100.263 49.7307 100.263 49.8294C100.362 49.928 100.658 51.0133 100.955 51.0133C101.152 51.0133 101.054 50.3227 101.054 50.224C101.054 49.928 100.955 49.632 100.856 49.4347C100.856 49.336 100.757 49.0401 100.757 49.0401C100.658 48.9414 100.658 48.6454 100.56 48.5467C100.56 48.3494 100.165 47.5601 99.8682 47.5601ZM102.535 51.408C102.733 51.3093 103.029 51.3093 103.326 51.3093L103.819 51.2107C103.918 51.112 104.017 51.0133 104.215 51.0133C104.313 50.9147 104.709 50.816 104.709 50.816C104.709 50.816 105.598 50.4214 105.696 50.4214C105.894 50.4214 106.289 50.52 106.289 50.816C106.289 51.0133 106.289 51.5067 106.19 51.6053C106.091 51.704 106.091 51.9013 106.091 51.9013L105.894 52.296C105.894 52.3946 105.696 52.4933 105.696 52.4933C105.499 52.592 105.301 52.888 105.202 52.888C105.005 52.9866 104.709 53.0853 104.511 53.0853C104.116 53.0853 103.721 53.184 103.326 53.184C102.832 53.184 102.239 52.592 102.14 52.1973C102.14 52.0986 102.041 51.8027 102.14 51.704C102.239 51.704 102.634 51.6053 102.535 51.408ZM103.819 54.4666C103.622 54.2693 103.424 54.2693 103.326 54.0719L103.227 53.9733C103.128 53.9733 103.029 53.9733 103.029 53.8746C102.93 53.7759 102.93 53.7759 102.832 53.7759C102.634 53.7759 102.93 53.6773 102.535 53.6773C102.437 53.6773 102.338 53.6773 102.338 53.6773H102.239L102.14 53.7759L102.041 53.8746V53.9733L102.14 54.0719C102.14 54.0719 102.239 54.1706 102.338 54.1706L102.437 54.2693L102.535 54.3679H102.634L102.733 54.4666H102.832H102.93L103.029 54.5653L103.128 54.6639V54.7626H103.227L103.326 54.8612V54.9599H103.424C103.523 55.0586 103.523 55.1572 103.622 55.1572H103.819L103.918 55.0586L104.017 54.9599V54.8612V54.7626V54.6639C103.622 54.6639 103.622 54.5653 103.819 54.4666ZM111.031 38.779C110.932 39.4696 110.339 40.1603 109.845 40.3576C109.746 40.4563 109.549 40.8509 109.549 40.8509C109.549 41.1469 109.648 41.2456 109.845 41.2456C109.944 41.2456 109.746 41.3442 110.043 41.3442C110.438 41.3442 110.833 41.3442 111.129 41.3442C111.524 41.3442 111.524 40.1603 111.426 39.8643C111.426 39.7656 111.327 39.4696 111.327 39.3709C111.327 39.2723 111.228 38.8776 111.228 38.8776C111.228 38.6803 111.129 38.6803 111.031 38.779Z" fill="#F5F3C6"/>
          <path d="M19.9537 43.7081C21.2379 43.7081 22.4233 44.2014 23.3123 45.1881C24.2013 46.1747 24.6952 47.4573 24.6952 48.8386V53.1799C24.6952 53.3772 24.5965 53.5745 24.3989 53.7719C24.2013 53.9692 24.0038 54.0679 23.8062 54.0679C23.6086 54.0679 23.4111 53.9692 23.2135 53.7719C23.016 53.5745 22.9172 53.3772 22.9172 53.1799V48.8386C22.9172 47.852 22.6208 47.0627 22.0281 46.372C21.4355 45.6814 20.744 45.3854 19.8549 45.3854C18.9659 45.3854 18.2744 45.6814 17.6818 46.372C17.0891 47.0627 16.7927 47.852 16.7927 48.8386V53.1799C16.7927 53.3772 16.6939 53.5745 16.4964 53.7719C16.2988 53.9692 16.1012 54.0679 15.9037 54.0679C15.7061 54.0679 15.4098 53.9692 15.311 53.7719C15.1134 53.5745 15.0146 53.3772 15.0146 53.1799V44.4974C15.0146 44.3001 15.1134 44.1028 15.311 43.9054C15.5086 43.7081 15.7061 43.6094 15.9037 43.6094C16.1012 43.6094 16.2988 43.7081 16.4964 43.9054C16.6939 44.1028 16.7927 44.3001 16.7927 44.4974V44.7934C17.7805 44.1028 18.7683 43.7081 19.9537 43.7081Z" fill="white"/>
          <path d="M32.2027 43.7081C33.4869 43.7081 34.6723 44.2014 35.5613 45.1881C36.4504 46.1747 36.9443 47.4573 36.9443 48.8386V53.1799C36.9443 53.3772 36.8455 53.5745 36.6479 53.7719C36.4504 53.9692 36.2528 54.0679 36.0552 54.0679C35.8577 54.0679 35.6601 53.9692 35.4625 53.7719C35.265 53.5745 35.1662 53.3772 35.1662 53.1799V48.8386C35.1662 47.852 34.8699 47.0627 34.2772 46.372C33.6845 45.6814 32.993 45.3854 32.104 45.3854C31.2149 45.3854 30.5235 45.6814 29.9308 46.372C29.3381 47.0627 29.0417 47.852 29.0417 48.8386V53.1799C29.0417 53.3772 28.943 53.5745 28.7454 53.7719C28.5478 53.9692 28.3503 54.0679 28.1527 54.0679C27.9551 54.0679 27.6588 53.9692 27.56 53.7719C27.3625 53.5745 27.2637 53.3772 27.2637 53.1799V44.4974C27.2637 44.3001 27.3625 44.1028 27.56 43.9054C27.7576 43.7081 27.9551 43.6094 28.1527 43.6094C28.3503 43.6094 28.5478 43.7081 28.7454 43.9054C28.943 44.1028 29.0417 44.3001 29.0417 44.4974V44.7934C30.0296 44.1028 31.1162 43.7081 32.2027 43.7081Z" fill="white"/>
          <path d="M44.2543 43.7082C45.6373 43.7082 46.8226 44.2015 47.9092 45.1882C48.8971 46.1748 49.391 47.4574 49.391 48.8387C49.391 50.22 48.8971 51.5027 47.9092 52.4893C46.9214 53.476 45.736 53.9693 44.2543 53.9693C42.8714 53.9693 41.686 53.476 40.5994 52.4893C39.6116 51.5027 39.1177 50.22 39.1177 48.8387C39.1177 47.3588 39.6116 46.1748 40.5994 45.1882C41.686 44.2015 42.8714 43.7082 44.2543 43.7082ZM44.2543 52.3907C45.1434 52.3907 46.0324 52.0947 46.6251 51.404C47.3165 50.7134 47.6129 49.924 47.6129 48.9374C47.6129 47.9508 47.3165 47.1614 46.6251 46.4708C45.9336 45.7801 45.1434 45.4841 44.2543 45.4841C43.3653 45.4841 42.4763 45.7801 41.8836 46.4708C41.1921 47.1614 40.8957 47.9508 40.8957 48.9374C40.8957 49.924 41.1921 50.7134 41.8836 51.404C42.575 51.996 43.3653 52.3907 44.2543 52.3907Z" fill="white"/>
          <path d="M59.8617 44.3002C59.8617 44.3988 59.9605 44.4975 59.9605 44.5962C59.9605 44.6948 59.9605 44.7935 59.8617 44.8922L56.2068 53.5746C56.108 53.8706 55.8116 54.068 55.4165 54.068C55.0214 54.068 54.725 53.8706 54.6263 53.5746L50.9713 44.8922C50.9713 44.7935 50.8726 44.6948 50.8726 44.5962C50.8726 44.4975 50.8726 44.3988 50.9713 44.3002C51.0701 44.1029 51.2677 43.9055 51.4652 43.8069C51.564 43.8069 51.6628 43.7082 51.7616 43.7082C51.8604 43.7082 51.9592 43.7082 52.0579 43.8069C52.2555 43.9055 52.4531 44.0042 52.5518 44.3002L55.4165 51.108L58.2812 44.3002C58.38 44.1029 58.5775 43.9055 58.7751 43.8069C58.8739 43.8069 58.9727 43.7082 59.0714 43.7082C59.1702 43.7082 59.269 43.7082 59.3678 43.8069C59.5653 43.9055 59.7629 44.0042 59.8617 44.3002Z" fill="white"/>
          <path d="M71.2216 43.7082C71.4192 43.7082 71.6168 43.8069 71.8143 44.0042C72.0119 44.2015 72.1107 44.3988 72.1107 44.5962V53.2786C72.1107 53.476 72.0119 53.6733 71.8143 53.8706C71.6168 54.068 71.4192 54.1666 71.2216 54.1666C71.0241 54.1666 70.8265 54.068 70.629 53.8706C70.4314 53.6733 70.3326 53.476 70.3326 53.2786V52.7853C69.3448 53.6733 68.2582 54.068 66.974 54.068C65.5911 54.068 64.4057 53.5746 63.3191 52.588C62.3313 51.6013 61.8374 50.3187 61.8374 48.9374C61.8374 47.4574 62.3313 46.2735 63.3191 45.2868C64.3069 44.3002 65.4923 43.8069 66.974 43.8069C68.2582 43.8069 69.3448 44.2015 70.3326 45.0895V44.6948C70.3326 44.4975 70.4314 44.3002 70.629 44.1029C70.7277 43.8069 70.9253 43.7082 71.2216 43.7082ZM66.974 52.3907C67.8631 52.3907 68.7521 52.0947 69.3448 51.404C70.0363 50.7134 70.3326 49.924 70.3326 48.9374C70.3326 47.9508 70.0363 47.1614 69.3448 46.4708C68.6533 45.7801 67.8631 45.4841 66.974 45.4841C66.085 45.4841 65.196 45.7801 64.6033 46.4708C63.9118 47.1614 63.6155 47.9508 63.6155 48.9374C63.6155 49.924 63.9118 50.7134 64.6033 51.404C65.196 51.996 65.9862 52.3907 66.974 52.3907Z" fill="white"/>
          <path d="M79.223 43.7082C79.4206 43.7082 79.6181 43.8068 79.8157 44.0042C80.0133 44.2015 80.112 44.3988 80.112 44.5962C80.112 44.7935 80.0133 44.9908 79.8157 45.1881C79.6181 45.3855 79.4206 45.4841 79.223 45.4841H77.8401V53.2786C77.8401 53.476 77.7413 53.6733 77.5437 53.8706C77.3462 54.0679 77.1486 54.1666 76.951 54.1666C76.7535 54.1666 76.5559 54.0679 76.3584 53.8706C76.1608 53.6733 76.062 53.476 76.062 53.2786V45.4841H74.6791C74.4815 45.4841 74.1852 45.3855 74.0864 45.1881C73.8888 44.9908 73.79 44.7935 73.79 44.5962C73.79 44.3988 73.8888 44.2015 74.0864 44.0042C74.2839 43.8068 74.4815 43.7082 74.6791 43.7082H76.062V41.0442C76.062 40.8469 76.1608 40.6496 76.3584 40.4522C76.5559 40.2549 76.7535 40.1562 76.951 40.1562C77.1486 40.1562 77.3462 40.2549 77.5437 40.4522C77.7413 40.6496 77.8401 40.8469 77.8401 41.0442V43.7082H79.223Z" fill="white"/>
          <path d="M83.174 40.255C83.3716 40.255 83.5691 40.255 83.6679 40.3537C83.7667 40.4523 83.9642 40.551 84.063 40.7483C84.1618 40.9457 84.2606 41.143 84.2606 41.3403C84.2606 41.5376 84.2606 41.735 84.1618 41.9323C84.063 42.1296 83.9642 42.2283 83.7667 42.327C83.5691 42.4256 83.3716 42.4256 83.174 42.4256C82.9764 42.4256 82.7789 42.4256 82.5813 42.327C82.3837 42.2283 82.285 42.1296 82.1862 41.9323C82.0874 41.735 82.0874 41.5376 82.0874 41.3403C82.0874 41.143 82.0874 40.9457 82.1862 40.7483C82.285 40.551 82.3837 40.4523 82.5813 40.3537C82.7789 40.255 82.9764 40.255 83.174 40.255ZM83.174 43.7083C83.3716 43.7083 83.5691 43.8069 83.7667 44.0042C83.9642 44.2016 84.063 44.3989 84.063 44.5962V53.2787C84.063 53.476 83.9642 53.6734 83.7667 53.8707C83.5691 54.068 83.3716 54.1667 83.174 54.1667C82.9764 54.1667 82.7789 54.068 82.5813 53.8707C82.3837 53.6734 82.285 53.476 82.285 53.2787V44.5962C82.285 44.3989 82.3837 44.2016 82.5813 44.0042C82.7789 43.8069 82.9764 43.7083 83.174 43.7083Z" fill="white"/>
          <path d="M11.1623 40.255C11.3598 40.255 11.5574 40.255 11.6562 40.3537C11.8538 40.4523 11.9525 40.551 12.0513 40.7483C12.1501 40.9457 12.2489 41.143 12.2489 41.3403C12.2489 41.5376 12.2489 41.735 12.1501 41.9323C12.0513 42.1296 11.9525 42.2283 11.755 42.327C11.4586 42.4256 11.3598 42.4256 11.1623 42.4256C10.9647 42.4256 10.7672 42.4256 10.5696 42.327C10.372 42.2283 10.2732 42.1296 10.1745 41.9323C10.0757 41.735 10.0757 41.5376 10.0757 41.3403C10.0757 41.143 10.0757 40.9457 10.1745 40.7483C10.2732 40.551 10.372 40.4523 10.5696 40.3537C10.7672 40.255 10.9647 40.255 11.1623 40.255ZM11.1623 43.7083C11.3598 43.7083 11.5574 43.8069 11.755 44.0042C11.9525 44.2016 12.0513 44.3989 12.0513 44.5962V53.2787C12.0513 53.476 11.9525 53.6734 11.755 53.8707C11.5574 54.068 11.3598 54.1667 11.1623 54.1667C10.9647 54.1667 10.7672 54.068 10.5696 53.8707C10.372 53.6734 10.2732 53.476 10.2732 53.2787V44.5962C10.2732 44.3989 10.372 44.2016 10.5696 44.0042C10.6684 43.8069 10.8659 43.7083 11.1623 43.7083Z" fill="white"/>
          <path d="M121.304 43.7081C122.588 43.7081 123.773 44.2014 124.662 45.1881C125.551 46.1747 126.045 47.4573 126.045 48.8386V53.1799C126.045 53.3772 125.947 53.5745 125.749 53.7719C125.551 53.9692 125.354 54.0679 125.156 54.0679C124.959 54.0679 124.761 53.9692 124.564 53.7719C124.366 53.5745 124.267 53.3772 124.267 53.1799V48.8386C124.267 47.852 123.971 47.0627 123.378 46.372C122.786 45.6814 122.094 45.3854 121.205 45.3854C120.316 45.3854 119.625 45.6814 119.032 46.372C118.439 47.0627 118.143 47.852 118.143 48.8386V53.1799C118.143 53.3772 118.044 53.5745 117.846 53.7719C117.649 53.9692 117.451 54.0679 117.254 54.0679C117.056 54.0679 116.76 53.9692 116.661 53.7719C116.464 53.5745 116.365 53.3772 116.365 53.1799V44.4974C116.365 44.3001 116.464 44.1028 116.661 43.9054C116.859 43.7081 117.056 43.6094 117.254 43.6094C117.451 43.6094 117.649 43.7081 117.846 43.9054C118.044 44.1028 118.143 44.3001 118.143 44.4974V44.7934C119.131 44.1028 120.118 43.7081 121.304 43.7081Z" fill="white"/>
          </g>
          </g>
          <defs>
          <clipPath id="clip0_72_2474">
          <rect width="133.948" height="57.62" fill="white"/>
          </clipPath>
          <clipPath id="clip1_72_2474">
          <rect width="133.948" height="57.62" fill="white"/>
          </clipPath>
          </defs>
          </svg>
        </div>
        <div class="column-container">
          <!-- Cột LoRaWAN -->
          <div class="column" id="lorawanTable">
            <table class="table">
              <tr class="header-row">
                <th colspan="3">PROTOCOL</th>
              </tr>
              <tr>
                <th>Mode</th>
                <td>
                  <select id="modeSelect" onchange="toggleMode()">
                    <option value="">-- Select Mode --</option>
                    <option value="WIFI">WIFI</option>
                    <option value="SIM4G">4G</option>
                    <option value="LORAWAN">LoRaWAN</option>
                  </select>
                </td>
              </tr>
              <!-- Ẩn bảng thông số chế độ wifi ban đầu -->
              <tr class="hidden" id="wifiSettings">
                <th>SSID</th>
                <td><input id="value22" type="text" /></td>
              </tr>
              <tr class="hidden" id="wifiSettings">
                <th>PASSWORD</th>
                <td><input id="value23" type="text" /></td>
              </tr>
              <!-- <tr class="hidden" id="sim4GSettings">
                <th>Send index</th>
                <td><input id="value24" type="text" /></td>
              </tr>
              <tr class="hidden" id="sim4GSettings">
                <th>Send value</th>
                <td><input id="value25" type="text" /></td>
              </tr> -->
              <tr class="hidden" id="lorawanSettings">
                <th>Mode LoRaWAN</th>
                <td>
                  <select id="modeLoraSelect" onchange="toggleModeLora()">
                    <option value="">-- Select Mode --</option>
                    <option value="ABP">ABP</option>
                    <option value="OTAA">OTAA</option>
                  </select>
                </td>
              </tr>
            <!-- Ẩn bảng thông số chế độ OTAA ban đầu -->
            <tr class="hidden" id="otaaSettings"> 
                <th>Class</th>
                <td>
                    <select id="classSelectOTAA" onchange="toggleClassLora()">
                        <option value="">-- Select Class --</option>
                        <option value="A">A</option>
                        <option value="C">C</option>
                    </select>
                </td>
            </tr>
            <tr class="hidden" id="otaaSettings">
                <th>Dev_EUI</th>
                <td><input id="value1" type="text" /></td>
            </tr>
            <tr class="hidden" id="otaaSettings">
                <th>APP_EUI</th>
                <td><input id="value2" type="text" /></td>
            </tr>
            <tr class="hidden" id="otaaSettings">
                <th>APP KEY</th>
                <td><input id="value3" type="text" /></td>
            </tr>
            <tr class="hidden" id="otaaSettings">
                <th>Interval</th>
                <td><input id="value4" type="text" /></td>
            </tr>
            <!-- Hiển thị bảng thông số chế độ ABP ban đầu -->
            <tr class="hidden" id="abpSettings">
                <th>Class</th>
                <td>
                    <select id="classSelectABP" onchange="toggleClassLora()">
                        <option value="">-- Select Class --</option>
                        <option value="A">A</option>
                        <option value="C">C</option>
                    </select>
                </td>
            </tr>
            <tr class="hidden" id="abpSettings">
                <th>Dev_addr</th>
                <td><input id="value5" type="text" /></td>
            </tr>
            <tr class="hidden" id="abpSettings">
                <th>NWK</th>
                <td><input id="value6" type="text" /></td>
            </tr>
            <tr class="hidden" id="abpSettings">
                <th>APPs KEY</th>
                <td><input id="value7" type="text" /></td>
            </tr>
            <tr class="hidden" id="abpSettings">
                <th>Interval</th>
                <td><input id="value8" type="text" /></td>
            </tr>
            </table>
          </div>
        </div>
      </div>

      <!--  RS485 -->
      <div class="frame">
        <div class="column-container">
          <div class="column" id="rs485Table">
            <table class="table">
              <tr class="header-row">
                <th colspan="3">RS485 Options:</th>
              </tr>
              <tr>
                <td colspan="3" class="centered">
                  <select id="rs485Options" onchange="toggleRS485Settings()">
                    <option value="">-- Select --</option>
                    <option value="Temp/Hum">Temp/Hum</option>
                    <option value="PH">PH</option>
                    <option value="custom">Customize</option>
                  </select>
                </td>
              </tr>
              <tr class="hidden-row tempHumSettings" >
                <td><b>BaudRates</b></td>
                <!-- <td>RS485</td> -->
                <td>9600</td>
              </tr>
              <tr class="hidden-row tempHumSettings" >
                <td><b>ByteSend</b></td>
                <!-- <td>RS485</td> -->
                <td>01 03 00 00 00 02</td>
              </tr>
              <tr class="hidden-row tempHumSettings" >
                <td><b>RS485 Configure</b></td>
                <!-- <td>RS485</td> -->
                <td>8N1</td>
              </tr>
              <tr class="hidden-row phSettings" >
                <td><b>BaudRates</b></td>
                <!-- <td>RS485</td> -->
                <td>9600</td>
              </tr>
              <tr class="hidden-row phSettings" >
                <td><b>ByteSend</b></td>
                <!-- <td>RS485</td> -->
                <td>01 03 00 00 00 02</td>
              </tr>
              <tr class="hidden-row phSettings" >
                <td><b>RS485 Configure</b></td>
                <!-- <td>RS485</td> -->
                <td>8N1</td>
              </tr>
              <tr class="hidden-row customSettings" style="font-weight: bold;">
                <td>BaudRates</td>
                <td><input id="value9" type="text" /></td>
              </tr>
              <tr class="hidden-row customSettings" style="font-weight: bold;">
                <td>ByteSend</td>
                <td><input id="value10" type="text" oninput="formatValue(this)" /></td>
              </tr>
              
              <tr class="hidden-row customSettings" style="font-weight: bold;">
                <td>RS485 Configure</td>
                <td><input id="value11" type="text" /></td>
              </tr>
            </table>
          </div>
        </div>
      </div>

      <!-- Data Send RS485 -->
      <div class="frame">
        <div class="column-container">
          <div class="column" id="rs485Table">
            <table class="table">
              <tr class="header-row">
                <th colspan="3">Send Data RS485:</th>
              </tr>
              <tr class="hidden-row tempHumSettings">
                <td><input id="tempInput" type="text" /></td>
                <td>RS485</td>
                <td>[3][4]</td>
              </tr>
              <tr class="hidden-row tempHumSettings">
                <td><input id="humInput" type="text" /></td>
                <td>RS485</td>
                <td>[5][6]</td>
              </tr>
              <tr class="hidden-row phSettings">
                <td><input id="tempInput1" type="text" /></td>
                <td>RS485</td>
                <td>[3][4]</td>
              </tr>
              <tr class="hidden-row phSettings">
                <td><input id="humInput1" type="text" /></td>
                <td>RS485</td>
                <td>[5][6]</td>
              </tr>
              <tr class="hidden-row customSettings">
                <td><input id="customInput1" type="text" /></td>
                <td>
                  <select id="ByteSelect1" onchange="toggleByte()">
                    <option value="">-- Select --</option>
                    <option value="1">[1]</option>
                    <option value="2">[2]</option>
                    <option value="3">[3]</option>
                    <option value="4">[4]</option>
                    <option value="5">[5]</option>
                    <option value="6">[6]</option>
                  </select>
                  <select id="ByteSelect2" onchange="toggleByte()">
                    <option value="">-- Select --</option>
                    <option value="1">[1]</option>
                    <option value="2">[2]</option>
                    <option value="3">[3]</option>
                    <option value="4">[4]</option>
                    <option value="5">[5]</option>
                    <option value="6">[6]</option>
                  </select>
                </td>
              </tr>
              <tr class="hidden-row customSettings">
                <td><input id="customInput3" type="text" /></td>
                <td>
                  <select id="ByteSelect3" onchange="toggleByte()">
                    <option value="">-- Select --</option>
                    <option value="1">[1]</option>
                    <option value="2">[2]</option>
                    <option value="3">[3]</option>
                    <option value="4">[4]</option>
                    <option value="5">[5]</option>
                    <option value="6">[6]</option>
                  </select>
                  <select id="ByteSelect4" onchange="toggleByte()">
                    <option value="">-- Select --</option>
                    <option value="1">[1]</option>
                    <option value="2">[2]</option>
                    <option value="3">[3]</option>
                    <option value="4">[4]</option>
                    <option value="5">[5]</option>
                    <option value="6">[6]</option>
                  </select>
                </td>
              </tr>
            </table>
          </div>
        </div>
      </div>
      <!-- DataSend -->
      <div class="frame">
        <div class="column-container">
          <div class="column" id="dataSendTable">
            <div class="data-send-container">
              <table class="table">
                <tr class="header-row">
                  <th colspan="4">DataSend</th>
                </tr>
                <tr class="hidden-row data-row" id="dataRow1">
                  <td><input type="text" id="value12" /></td>
                  <td>
                    <select id="dataType1" onchange="toggleDataType(this)">
                      <option value="">-- Select --</option>
                      <option value="Digital">Digital</option>
                      <option value="Analog">Analog</option>
                      <option value="Customize">Customize</option>
                    </select>
                  </td>
                  <td class="data-inputs analog-inputs">
                    <input type="text" id="value30" class="input-small" /> -
                    <input type="text" id="value31" class="input-small" />
                  </td>
                  <td class="data-inputs digital-inputs">
                    <input type="text" id="value13" />
                  </td>
                  <td>
                    <button type="button" onclick="removeDataRow(this)">
                      -
                    </button>
                  </td>
                </tr>
                <tr class="hidden-row data-row" id="dataRow2">
                  <td><input type="text" id="value14" /></td>
                  <td>
                    <select id="dataType2" onchange="toggleDataType(this)">
                      <option value="">-- Select --</option>
                      <option value="Digital">Digital</option>
                      <option value="Analog">Analog</option>
                      <option value="Customize">Customize</option>
                    </select>
                  </td>
                  <td class="data-inputs analog-inputs">
                    <input type="text" id="value32" class="input-small" /> -
                    <input type="text" id="value33" class="input-small" />
                  </td>
                  <td class="data-inputs digital-inputs">
                    <input type="text" id="value15" />
                  </td>
                  <td>
                    <button type="button" onclick="removeDataRow(this)">
                      -
                    </button>
                  </td>
                </tr>
                <tr class="hidden-row data-row" id="dataRow3">
                  <td><input type="text" id="value16" /></td>
                  <td>
                    <select id="dataType3" onchange="toggleDataType(this)">
                      <option value="">-- Select --</option>
                      <option value="Digital">Digital</option>
                      <option value="Analog">Analog</option>
                      <option value="Customize">Customize</option>
                    </select>
                  </td>
                  <td class="data-inputs analog-inputs">
                    <input type="text" id="value34" class="input-small" /> -
                    <input type="text" id="value35" class="input-small" />
                  </td>
                  <td class="data-inputs digital-inputs">
                    <input type="text" id="value17" />
                  </td>
                  <td>
                    <button type="button" onclick="removeDataRow(this)">
                      -
                    </button>
                  </td>
                </tr>
                <tr class="hidden-row data-row" id="dataRow4">
                  <td><input type="text" id="value18" /></td>
                  <td>
                    <select id="dataType4" onchange="toggleDataType(this)">
                      <option value="">-- Select --</option>
                      <option value="Digital">Digital</option>
                      <option value="Analog">Analog</option>
                      <option value="Customize">Customize</option>
                    </select>
                  </td>
                  <td class="data-inputs analog-inputs">
                    <input type="text" id="value36" class="input-small" /> -
                    <input type="text" id="value37" class="input-small" />
                  </td>
                  <td class="data-inputs digital-inputs">
                    <input type="text" id="value19" />
                  </td>
                  <td>
                    <button type="button" onclick="removeDataRow(this)">
                      -
                    </button>
                  </td>
                </tr>
                <tr class="hidden-row data-row" id="dataRow5">
                  <td><input type="text" id="value20" /></td>
                  <td>
                    <select id="dataType5" onchange="toggleDataType(this)">
                      <option value="">-- Select --</option>
                      <option value="Digital">Digital</option>
                      <option value="Analog">Analog</option>
                      <option value="Customize">Customize</option>
                    </select>
                  </td>
                  <td class="data-inputs analog-inputs">
                    <input type="text" id="value38" class="input-small" /> -
                    <input type="text" id="value39" class="input-small" />
                  </td>
                  <td class="data-inputs digital-inputs">
                    <input type="text" id="value21" />
                  </td>
                  <td>
                    <button type="button" onclick="removeDataRow(this)">
                      -
                    </button>
                  </td>
                </tr>
              </table>
            </div>
          </div>
        </div>
      </div>
      <div class="button">
        <button type="button" onclick="toggleDataRows()">+</button>
        <button type="button" onclick="sendValues()">Send</button>
      </div>
      <div class="button">
        <form id="uploadForm" method="POST" enctype="multipart/form-data" style="display: inline">
          <input type="file" name="update" />
          <button type="button" onclick="updateFirmware()">updateOTA</button>
        </form>
      </div>
      <div id="firmwareStatus"></div>
      </div>
    </div>
  </body>
</html>
)=====";