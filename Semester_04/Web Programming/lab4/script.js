function addPlayer() {
    const playerName = document.getElementById('playerName').value;
    const playerAge = document.getElementById('playerAge').value;
    const birthPlace = document.getElementById('birthPlace').value;

    if (!playerName || !playerAge || !birthPlace) {
        alert('please fill in all fields');
        return;
    }

    const tbody = document.getElementById('tabel').getElementsByTagName('tbody')[0];
    const newRow = tbody.insertRow();

    const cells = [
        newRow.insertCell(0),
        newRow.insertCell(1),
        newRow.insertCell(2)
    ];

    cells[0].textContent = playerName;
    cells[1].textContent = playerAge;
    cells[2].textContent = birthPlace;

    document.getElementById('playerName').value = '';
    document.getElementById('playerAge').value = '';
    document.getElementById('birthPlace').value = '';
};

document.addEventListener('DOMContentLoaded', function() {
    const table = document.getElementById('tabel');
    const headers = table.getElementsByTagName('th');
    let sortDirection = 1; // 1 crescator, -1 descrescator

    // event listeners pt fiecare coloana
    for (let i = 0; i < headers.length; i++) {
        headers[i].addEventListener('click', function() {
            sortTable(i);
        });
    }

    function sortTable(columnIndex) {
        const tbody = table.getElementsByTagName('tbody')[0];
        const rows = Array.from(tbody.getElementsByTagName('tr'));
        const columnValues = rows.map(row => row.getElementsByTagName('td')[columnIndex].textContent);
    
        columnValues.sort((a, b) => {
            if (!isNaN(a) && !isNaN(b)) {
                return sortDirection * (parseFloat(a) - parseFloat(b)); // numere 
            } else {
                return sortDirection * a.localeCompare(b); //strings
            }
        });

        rows.forEach((row, index) => {
            row.getElementsByTagName('td')[columnIndex].textContent = columnValues[index];
        });  
        sortDirection *= -1;
    }
}); 