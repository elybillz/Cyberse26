// products.js — Terra Tribe Fashion

// --- SEARCH FILTER ---
var searchInput = document.getElementById('search-input');
var cards = document.getElementsByClassName('product-card');
var noResults = document.getElementById('no-results');

function filterProducts() {
  var query = searchInput.value.toLowerCase();
  var count = 0;

  for (var i = 0; i < cards.length; i++) {
    var name = cards[i].getAttribute('data-name').toLowerCase();
    if (name.includes(query)) {
      cards[i].style.display = '';
      count++;
    } else {
      cards[i].style.display = 'none';
    }
  }

  if (count === 0) {
    noResults.style.display = 'block';
  } else {
    noResults.style.display = 'none';
  }
}

searchInput.addEventListener('input', filterProducts);
