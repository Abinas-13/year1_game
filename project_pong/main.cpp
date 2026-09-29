#include <SFML/Graphics.hpp>

// Controls: Player1 (A/Z), Player2 (Up/Down)
const sf::Keyboard::Key controls[4] = {
    sf::Keyboard::A,   // Player1 UP
    sf::Keyboard::Z,   // Player1 Down
    sf::Keyboard::Up,  // Player2 UP
    sf::Keyboard::Down // Player2 Down
};

// Parameters
const sf::Vector2f paddleSize(25.f, 100.f);
const float ballRadius = 10.f;
const int gameWidth = 800;
const int gameHeight = 600;
const float paddleSpeed = 400.f;
const float paddleOffsetWall = 10.f;
const float time_step = 0.017f; // 60 fps

// Objects
sf::CircleShape ball;
sf::RectangleShape paddles[2];

// Ball velocity
sf::Vector2f ballVelocity(300.f, 300.f);

void init()
{
    // Paddle setup
    for (sf::RectangleShape& p : paddles) {
        p.setSize(paddleSize);
        p.setOrigin(paddleSize / 2.f);
    }

    // Ball setup
    ball.setRadius(ballRadius);
    ball.setOrigin(ballRadius, ballRadius);

    // Paddle positions
    paddles[0].setPosition(paddleOffsetWall + paddleSize.x / 2.f, gameHeight / 2.f);
    paddles[1].setPosition(gameWidth - paddleOffsetWall - paddleSize.x / 2.f, gameHeight / 2.f);

    // Ball position
    ball.setPosition(gameWidth / 2.f, gameHeight / 2.f);
}

void update(float dt)
{
    // Player 1 movement (A/Z)
    float direction1 = 0.f;
    if (sf::Keyboard::isKeyPressed(controls[0])) direction1 -= 1.f;
    if (sf::Keyboard::isKeyPressed(controls[1])) direction1 += 1.f;
    paddles[0].move(sf::Vector2f(0.f, direction1 * paddleSpeed * dt));

    // Player 2 movement (Up/Down)
    float direction2 = 0.f;
    if (sf::Keyboard::isKeyPressed(controls[2])) direction2 -= 1.f;
    if (sf::Keyboard::isKeyPressed(controls[3])) direction2 += 1.f;
    paddles[1].move(sf::Vector2f(0.f, direction2 * paddleSpeed * dt));

    // Clamp paddle positions
    for (int i = 0; i < 2; i++)
    {
        sf::Vector2f pos = paddles[i].getPosition();

        if (pos.y < paddleSize.y / 2.f)
            pos.y = paddleSize.y / 2.f;

        if (pos.y > gameHeight - paddleSize.y / 2.f)
            pos.y = gameHeight - paddleSize.y / 2.f;

        paddles[i].setPosition(pos);
    }

    // Ball movement
    ball.move(ballVelocity * dt);

    // Ball bounce top/bottom
    if (ball.getPosition().y <= ballRadius || ball.getPosition().y >= gameHeight - ballRadius)
        ballVelocity.y = -ballVelocity.y;

    // Ball bounce left paddle
    if (ball.getGlobalBounds().intersects(paddles[0].getGlobalBounds()))
        ballVelocity.x = std::abs(ballVelocity.x);

    // Ball bounce right paddle
    if (ball.getGlobalBounds().intersects(paddles[1].getGlobalBounds()))
        ballVelocity.x = -std::abs(ballVelocity.x);

    // Ball reset if out of bounds
    if (ball.getPosition().x < 0 || ball.getPosition().x > gameWidth)
    {
        ball.setPosition(gameWidth / 2.f, gameHeight / 2.f);
        ballVelocity = sf::Vector2f(300.f, 300.f);
    }
}

void render(sf::RenderWindow& window)
{
    window.draw(paddles[0]);
    window.draw(paddles[1]);
    window.draw(ball);
}

void clean()
{
    // Nothing to clean for now
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight), "PONG");
    sf::Clock clock;

    init();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float dt = clock.restart().asSeconds();

        window.clear();
        update(dt);
        render(window);

        sf::sleep(sf::seconds(time_step));
        window.display();
    }

    clean();
    return 0;
}
