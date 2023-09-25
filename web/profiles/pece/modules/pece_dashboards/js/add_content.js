window.onload = function() {
    var btn = document.getElementById("artifacts_menu")
    btn.onclick = displayArtifactItems
}

function displayArtifactItems()
{
    items = document.getElementsByClassName("artifacts_items")[0]
    items.classList.toggle('hide')
}