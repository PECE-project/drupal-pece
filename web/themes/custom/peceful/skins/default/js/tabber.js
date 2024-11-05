// This script manages tab behavior in node--pece-essay--full.html.twig,
// where content is structured in tabs with associated divs.

const tabColumns = document.querySelectorAll(".panel-panel-inner > [id^=tabs-0-column]");

tabColumns.forEach((tabColumn) => {
  const tabLinks = tabColumn.querySelectorAll('ul li [href^="#tabs-"]');
  const tabContainers = tabColumn.querySelectorAll(".item-list");

  // Add bulma tab classes to the container
  tabContainers.forEach((container) => {
    container.classList.add("tabs", "is-boxed", "is-left", "is-small");
  });

  const tabDivs = Array.from(tabLinks).map(link => {
    const contentDiv = tabColumn.querySelector(link.hash);
    contentDiv.classList.add("hidden");
    return contentDiv;
  });

  tabColumn.addEventListener("click", (event) => {
    const clickedLink = event.target.closest('[href^="#tabs-"]');
    if (!clickedLink) return; // Ignore clicks outside of tab links
    event.preventDefault();

    // Deactive all the tabs
    tabDivs.forEach(div => div.classList.add("hidden"));
    tabLinks.forEach(link => link.parentNode.classList.remove("is-active"));

    const targetDiv = tabColumn.querySelector(clickedLink.hash);
    targetDiv.classList.remove("hidden");
    clickedLink.parentNode.classList.add("is-active");
  });

  // Make the first of each active
  const firstTabLink = tabLinks[0];
  const firstTabDiv = tabDivs[0];
  firstTabLink.parentNode.classList.add("is-active");
  firstTabDiv.classList.remove("hidden");
});
