// home.js — Terra Tribe Fashion

// --- BACK TO TOP BUTTON ---
var backToTop = document.getElementById('back-to-top');

window.addEventListener('scroll', function () {
  if (window.scrollY > 300) {
    backToTop.classList.add('visible');
  } else {
    backToTop.classList.remove('visible');
  }
});

backToTop.addEventListener('click', function () {
  window.scrollTo(0, 0);
});
