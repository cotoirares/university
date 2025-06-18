$(document).ready(function() {
    let previousNumbers = [];

    $('#generateChart').on('click', function() {
        // split
        const input = $('#numberInput').val();
        const numbers = input.split(',').map(num => parseFloat(num.trim())).filter(num => !isNaN(num));
        
        if (numbers.length === 0) {
            alert('please enter at least 1 number');
            return;
        }

        const maxValue = Math.max(...numbers);
        // prima data cand generez
        if (previousNumbers.length === 0) {
            $('#chart').empty();
            numbers.forEach((num, index) => {
                const bar = $('<div>')
                    .addClass('bar')
                    .attr('data-value', num)
                    .css({
                        'height': '0%',
                        'width': `${100 / numbers.length}%`
                    });

                $('#chart').append(bar);
                setTimeout(() => {
                    bar.css('height', `${(num / maxValue) * 100}%`);
                }, 50 * index);
            });
        } else {
            numbers.forEach((num, index) => {
                let bar;
                if (index < previousNumbers.length) {
                    // am bara
                    bar = $('#chart .bar').eq(index);
                    bar.attr('data-value', num);
                    if (num !== previousNumbers[index]) {
                        bar.css('height', `${(num / maxValue) * 100}%`);
                    }
                } else {
                    bar = $('<div>')
                        .addClass('bar')
                        .attr('data-value', num)
                        .css({
                            'height': '0%',
                            'width': `${100 / numbers.length}%`
                        });

                    $('#chart').append(bar);
                    setTimeout(() => {
                        bar.css('height', `${(num / maxValue) * 100}%`);
                    }, 50 * index);
                }
            });
            if (numbers.length < previousNumbers.length) {
                $('#chart .bar').slice(numbers.length).remove();
            }
        }
        previousNumbers = [...numbers];
    });
}); 