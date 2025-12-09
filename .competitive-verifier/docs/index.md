C++ version: C++17

<details>
  <summary>Referenced libraries</summary>
    
  <ul>
    <li>[beet](https://beet-aizu.github.io/library/)</li>
    <li>[CP Algorithms](https://cp-algorithms.github.io/cp-algorithms-aux/)</li>
    <li>[ei1333](https://ei1333.github.io/library/)</li>
    <li>[hitonanode](https://hitonanode.github.io/cplib-cpp/)</li>
    <li>[maspy](https://maspypy.github.io/library/)</li>
    <li>[Nachia](https://nachiavivias.github.io/cp-library/cpp/)</li>
    <li>[noshi91](https://noshi91.github.io/Library/)</li>
    <li>[Nyaan](https://nyaannyaan.github.io/library/)</li>
    <li>[sotanishy](https://sotanishy.github.io/cp-library-cpp/)</li>
    <li>[suisen](https://suisen-cp.github.io/cp-library-cpp/)</li>
    <li>[tko919](https://tko919.github.io/library/)</li>
  </ul>
</details>

<details>
<summary>Recent Commits</summary>

<ul id="recent-commits">
  <li>Loading recent commits...</li>
</ul>

<script>
async function loadRecentCommits() {
  const listElement = document.getElementById('recent-commits');

  try {
    const response = await fetch('https://api.github.com/repos/imsuck/library/commits?per_page=5');
    const commits = await response.json();

    // Clear loading message
    listElement.innerHTML = '';

    // Add commit items
    commits.forEach(commit => {
      const li = document.createElement('li');
      const shortSha = commit.sha.substring(0, 7);
      const message = commit.commit.message.split('\n')[0]; // Get first line only

      li.innerHTML = `<code>${shortSha}</code> ${message}`;
      listElement.appendChild(li);
    });

    // Add timestamp
    const timestampLi = document.createElement('li');
    timestampLi.style.fontStyle = 'italic';
    timestampLi.style.opacity = '0.7';
    timestampLi.textContent = `Updated on ${new Date().toLocaleDateString()} ${new Date().toLocaleTimeString()}`;
    listElement.appendChild(timestampLi);

  } catch (error) {
    listElement.innerHTML = '<li>Failed to load recent commits</li>';
    console.error('Error loading commits:', error);
  }
}

// Load commits when the page loads
document.addEventListener('DOMContentLoaded', loadRecentCommits);

// Also load when the details element is opened (in case it was cached)
document.querySelector('details summary').addEventListener('click', function() {
  const details = this.parentElement;
  if (details.open && document.getElementById('recent-commits').children.length === 1 &&
      document.getElementById('recent-commits').children[0].textContent === 'Loading recent commits...') {
    loadRecentCommits();
  }
});
</script>
</details>
