document.addEventListener('DOMContentLoaded', (event) => {
    document.getElementById('menu=toggle').addEventListener('click', function() {
        const menu = document.getElementById('menu')
    })
})



// const searchInputmakanan = document.getElementById('searchmakanan');
// const menuListmakanan = document.getElementById('menumakanan');

// const foods = [
//     "Cumi Balado",
//     "Kangkung",
//     "Pepes tahu",
//     "Mie Goreng",
//     "Rendang",
//     "Ayam Bakar",
//     "Ayam Geprek",
//     "Ayam Goreng",
//     "Tumis Toge",
//     "Tumis Kacang Panjang",
//     "Kentang Balado",
//     "Sayur Asem",
//     "Sayur Sop",
//     "Tongkol Balado",
//     "Ikan Kembung Goreng",
//     "Ikan Bawal Goreng",
//     "Bakwan Udang",
//     "Perkedel Jagung",
//     "Tempe Mendoan",
//     "Tempe Goreng", 
//     "Gehu",
//     "Kikil Balado",
//     "Pepes Peda",

// ];

// // Fungsi untuk menampilkan makanan
// function displayFoods(foods) {
//     menuListmakanan.innerHTML = '';
//     foods.forEach(food => {
//         const li = document.createElement('li');
//         li.textContent = food;
//         menuListmakanan.appendChild(li);
//     });
// }

// // Fungsi untuk mencari makanan
// function searchFoods(event) {
//     const searchText = event.target.value.toLowerCase();
//     const filteredFoods = foods.filter(food => 
//         food.toLowerCase().includes(searchText)
//     );
//     displayFoods(filteredFoods);
// }

// // Event listener untuk pencarian
// searchInputmakanan.addEventListener('input', searchFoods);

// // Tampilkan semua makanan saat halaman dimuat
// document.getElementById("list_menu_makanan").innerText = displayFoods(foods);;   

// const searchInputminuman = document.getElementById('searchminuman');
// const menuListminuman = document.getElementById('menuminuman');

// const drink = [
//     "Es Teh Manis",
//     "Es Teh Tawar",
//     "Teh Manis Panas",
//     "Teh Tawar Panas",
//     "Es Kopi",
//     "Kopi Panas",
//     "Es Jeruk Peras",
//     "Jeruk Peras Panas",
// ];

// // Fungsi untuk menampilkan makanan
// function displayDrink(drink) {
//     menuListminuman.innerHTML = '';
//     drink.forEach(drink => {
//         const li = document.createElement('li');
//         li.textContent = drink;
//         menuListminuman.appendChild(li);
//     });
// }

// // Fungsi untuk mencari makanan
// function searchDrink(event) {
//     const searchText = event.target.value.toLowerCase();
//     const filteredDrink = drink.filter(drink => 
//         drink.toLowerCase().includes(searchText)
//     );
//     displayDrink(filteredDrink);
// }

// // Event listener untuk pencarian
// searchInputminuman.addEventListener('input', searchDrink);

// // Tampilkan semua makanan saat halaman dimuat
// displayDrink(drink);