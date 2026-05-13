#include "Config.h"

const GUID PROVIDER_GUID = {
    0xa1b2c3d4, 0xe5f6, 0x7890,
    { 0xab, 0xcd, 0xef, 0x12, 0x34, 0x56, 0x78, 0x90 }
};

const GUID SUBLAYER_GUID = {
    0xb2c3d4e5, 0xf6a1, 0x8901,
    { 0xbc, 0xde, 0xf0, 0x12, 0x34, 0x56, 0x78, 0x91 }
};

const std::vector<std::string> domains = {
    // OpenAI (ChatGPT & API)
    "chatgpt.com", "openai.com", "api.openai.com", "auth.openai.com",
    "cdn.openai.com", "platform.openai.com", "chat.openai.com",

    // Anthropic (Claude & API)
    "claude.ai", "anthropic.com", "api.anthropic.com", "console.anthropic.com",

    // Google (Gemini, Bard, Vertex AI API)
    "gemini.google.com", "bard.google.com", "aistudio.google.com", 
    "generativelanguage.googleapis.com",

    // Microsoft / xAI / Groq / Perplexity
    "bing.com", "copilot.microsoft.com", "x.ai", "api.x.ai", "grok.com",
    "groq.com", "api.groq.com", "console.groq.com",
    "perplexity.ai", "api.perplexity.ai",

    // DeepSeek (China)
    "deepseek.com", "chat.deepseek.com", "api.deepseek.com", "platform.deepseek.com",

    // Mistral AI
    "mistral.ai", "chat.mistral.ai", "api.mistral.ai", "console.mistral.ai",

    // Hugging Face
    "huggingface.co", "huggingface.chat", "api-inference.huggingface.co",

    // Cohere
    "cohere.com", "api.cohere.com", "api.cohere.ai", "dashboard.cohere.com",

    // Replicate
    "replicate.com", "api.replicate.com",

    // Together AI
    "together.ai", "api.together.xyz", "api.together.ai",

    // Midjourney
    "midjourney.com", "api.midjourney.com",

    // Ollama (registry metadata and models download)
    "ollama.com", "ollama.ai", "registry.ollama.ai", 

    // Character.AI
    "character.ai", "beta.character.ai", "api.character.ai",

    // Poe & Other chatbots
    "poe.com", "api.poe.com",
    "phind.com", "you.com",

    // Runway (Image Generation)
    "runwayml.com", "api.runwayml.com",

    // Leonardo AI (Video/Image Generation)
    "leonardo.ai", "app.leonardo.ai", "api.leonardo.ai",

    // Stability AI (Stable Diffusion API)
    "stability.ai", "api.stability.ai", "clipdrop.co",

    // Reka AI
    "reka.ai", "chat.reka.ai", "api.reka.ai",

    // Fireworks AI
    "fireworks.ai", "api.fireworks.ai",

    // Grok / xAI related (extra)
    "console.x.ai",

    // OpenRouter (Multi-model interface)
    "openrouter.ai",

    // LangChain & LangSmith
    "langchain.com", "api.smith.langchain.com", "smith.langchain.com"
};

const std::string HOSTS_PATH = "C:\\Windows\\System32\\drivers\\etc\\hosts";