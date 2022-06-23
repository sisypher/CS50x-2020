document.querySelectorAll('.accordion-button').forEach(item => {
    item.addEventListener('click', (event) => {

        let accCollapse = item.nextElementSibling;

        if(!item.classList.contains('open')) {

            accCollapse.style.display = 'block';
            let accHeight = accCollapse.clientHeight;
            
            setTimeout(() => {
                accCollapse.style.height = accHeight + 'px';
                accCollapse.style.display = '';
            }, 1);

            item.nextElementSibling.classList = 'accordion-collapse acc-collapsing';

            setTimeout(() => {
                item.nextElementSibling.classList = 'accordion-collapse open';
            }, 300);
        }

        else {
            item.nextElementSibling.classList = 'accordion-collapse acc-collapsing';

            setTimeout(() => {
                accCollapse.style.height = '0px';
            }, 1);

            setTimeout(() => {
                item.nextElementSibling.classList = 'accordion-collapse collapsed';
                accCollapse.style.height = '';
            }, 300);
        }

      item.classList.toggle('open');
    });
  });