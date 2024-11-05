// This js is attached as a library to node--pece-essay--full.html.twig to handle 
// scraped and imported content with tabs and corresponding divs

const tabLinks = document.querySelectorAll('ul li [href^="#tabs-"]');
const tabContainers = document.querySelectorAll('.item-list');

// Add bulma tab classes to the containers 
tabContainers.forEach(tabContainer => {
  tabContainer.classList.add("tabs", "is-boxed", "is-left", "is-small");  
});

let tabDivs = [];

tabLinks.forEach(tabLink => {  
  const linkedDiv = document.querySelector(tabLink.hash);
  tabDivs.push(linkedDiv);
  linkedDiv.classList.add('hidden');

  tabLink.addEventListener('click', (e) => {
    e.preventDefault();

    tabDivs.forEach(tabDiv => {
      tabDiv.classList.add('hidden');
    });
    
    tabLinks.forEach( nonActiveLink => {
      nonActiveLink.parentNode.classList.remove("is-active");
    }); 

    linkedDiv.classList.remove('hidden');
    tabLink.parentNode.classList.add("is-active");
  });
});
