// inquiries.js — Terra Tribe Fashion

// --- INQUIRY FORM VALIDATION ---
var inquiryForm = document.getElementById('inquiry-form');

inquiryForm.addEventListener('submit', function (e) {
  e.preventDefault();

  var name    = document.getElementById('inq-name').value.trim();
  var email   = document.getElementById('inq-email').value.trim();
  var message = document.getElementById('inq-message').value.trim();
  var isValid = true;

  document.getElementById('err-inq-name').style.display    = 'none';
  document.getElementById('err-inq-email').style.display   = 'none';
  document.getElementById('err-inq-message').style.display = 'none';

  if (name === '') {
    document.getElementById('err-inq-name').style.display = 'block';
    isValid = false;
  }
  
  if (email === '' || !email.includes('@')) {
    document.getElementById('err-inq-email').style.display = 'block';
    isValid = false;
  }
  
  if (message === '') {
    document.getElementById('err-inq-message').style.display = 'block';
    isValid = false;
  }

  if (isValid) {
    inquiryForm.reset();
    document.getElementById('inq-success').style.display = 'block';
  }
});

// --- APPOINTMENT FORM VALIDATION ---
var apptForm = document.getElementById('appt-form');

apptForm.addEventListener('submit', function (e) {
  e.preventDefault();

  var name  = document.getElementById('appt-name').value.trim();
  var email = document.getElementById('appt-email').value.trim();
  var phone = document.getElementById('appt-phone').value.trim();
  var city  = document.getElementById('appt-city').value;
  var date  = document.getElementById('appt-date').value;
  var time  = document.getElementById('appt-time').value;
  var isValid = true;

  document.getElementById('err-appt-name').style.display  = 'none';
  document.getElementById('err-appt-email').style.display = 'none';
  document.getElementById('err-appt-phone').style.display = 'none';
  document.getElementById('err-appt-city').style.display  = 'none';
  document.getElementById('err-appt-date').style.display  = 'none';
  document.getElementById('err-appt-time').style.display  = 'none';

  if (name === '') {
    document.getElementById('err-appt-name').style.display = 'block';
    isValid = false;
  }
  
  if (email === '' || !email.includes('@')) {
    document.getElementById('err-appt-email').style.display = 'block';
    isValid = false;
  }	
  if (phone === '') {
    document.getElementById('err-appt-phone').style.display = 'block';
    isValid = false;
  }
  if (city === '') {
    document.getElementById('err-appt-city').style.display = 'block';
    isValid = false;
  }
  if (date === '') {
    document.getElementById('err-appt-date').style.display = 'block';
    isValid = false;
  }
  if (time === '') {
    document.getElementById('err-appt-time').style.display = 'block';
    isValid = false;
  }

  if (isValid) {
    apptForm.reset();
    document.getElementById('appt-success').style.display = 'block';
  }
});
