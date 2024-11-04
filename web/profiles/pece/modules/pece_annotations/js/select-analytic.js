const entities = document.querySelectorAll(".views-row");
const submitButtton = document.querySelector('#edit-submit');
entities.forEach((entity) => {
    entity.onclick = function () {
        checkbox = entity.querySelector('.form-checkbox');
        checkbox.checked = true;
        submitButtton.click();
    }
});