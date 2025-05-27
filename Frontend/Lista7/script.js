document.addEventListener("DOMContentLoaded", () => {
    const form = document.getElementById("add-todo-form");
    const input = form.querySelector("input[name='todo-name']");
    const list = document.getElementById("todo-list");
    const counter = document.getElementById("count");
    const clearBtn = document.getElementById("todos-clear");
  
    let todos = [];
  
    function initializeFromDOM() {
      const items = list.querySelectorAll("li");
      todos = Array.from(items).map((li) => {
        const name = li.querySelector(".todo-name").textContent.trim();
        const completed = li.classList.contains("todo__container--completed");
        return { name, completed };
      });
      render();
    }
  
    function render() {
      list.innerHTML = "";
      
      todos.forEach((todo, index) => {
        const li = document.createElement("li");
        li.classList.add("todo__container");
        if (todo.completed) {
          li.classList.add("todo__container--completed");
        }
  
        const nameDiv = document.createElement("div");
        nameDiv.className = "todo-element todo-name";
        nameDiv.textContent = todo.name;
        li.appendChild(nameDiv);
  
        const upBtn = createButton("↑", "move-up", () => {
          if (index > 0) {
            [todos[index], todos[index - 1]] = [todos[index - 1], todos[index]];
            render();
          }
        });
  
        const downBtn = createButton("↓", "move-down", () => {
          if (index < todos.length - 1) {
            [todos[index], todos[index + 1]] = [todos[index + 1], todos[index]];
            render();
          }
        });
  
        const toggleBtn = createButton(todo.completed ? "Revert" : "Done", "", () => {
          todos[index].completed = !todos[index].completed;
          render();
        });
  
        const removeBtn = createButton("Remove", "", () => {
          todos.splice(index, 1);
          render();
        });

        li.append(upBtn, downBtn, toggleBtn, removeBtn);
        
        list.appendChild(li);
      });
  
      updateCounter();
    }
  
    function updateCounter() {
      const remaining = todos.filter(todo => !todo.completed).length;
      counter.textContent = remaining;
    }
  
    function createButton(text, extraClass, onClick) {
      const btn = document.createElement("button");
      btn.textContent = text;
      btn.classList.add("todo-element", "todo-button");
      if (extraClass) btn.classList.add(extraClass);
      btn.addEventListener("click", onClick);
      return btn;
    }
  
    form.addEventListener("submit", (e) => {
      e.preventDefault();
      const value = input.value.trim();
      if (value !== "") {
        todos.push({ name: value, completed: false });
        input.value = "";
        render();
      }
    });
  
    clearBtn.addEventListener("click", () => {
      todos = [];
      render();
    });
  
    initializeFromDOM();
});
  