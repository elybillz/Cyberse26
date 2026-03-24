// trustees.js — Terra Tribe Fashion

// --- CLICK TO SHOW/HIDE EMAIL ---
var cards = document.querySelectorAll('.trustee-card');

for (var i = 0; i < cards.length; i++) {
  cards[i].addEventListener('click', function () {
    var email = this.querySelector('.trustee-email');
    if (email.style.display === 'block') {
      email.style.display = 'none';
    } else {
      email.style.display = 'block';
    }
  });
}
