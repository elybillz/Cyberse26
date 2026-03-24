// events.js — Terra Tribe Fashion

// --- CITY FILTER ---
var buttons = document.querySelectorAll('.filter-btn');
var cards   = document.querySelectorAll('.event-card');

for (var i = 0; i < buttons.length; i++) {
  buttons[i].addEventListener('click', function () {

    // set active button
    for (var j = 0; j < buttons.length; j++) {
      buttons[j].classList.remove('active');
    }
    this.classList.add('active');

    // show or hide cards
    var filter = this.getAttribute('data-filter');
    for (var k = 0; k < cards.length; k++) {
      if (filter === 'all' || cards[k].getAttribute('data-city') === filter) {
        cards[k].style.display = '';
      } else {
        cards[k].style.display = 'none';
      }
    }

  });
}
