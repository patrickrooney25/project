# M0 Design and Understanding Note

Answer briefly in your own words. This is not intended to be a long report.

1. What responsibility belongs to `Workspace`, and what responsibilities belong to `Document`, `Prompt`, and `Message` instead?

Document, Prompt, and Message are individual objects
that store their own data and behaviors. Workspace is a container class that logically groups a context and manages the collections of the underlying objects.

2. Why are the collections inside `Workspace` private? Explain the purpose of the const and non-const `At` overloads.

The collections are private to prevent external code from directly modifying vector storage or invalidating internal state. The non-const at overloads allow code to retrieve a mutable reference to modify a stored item in place. The const overloads ensure read only access when operating on a const workspace without creating unnecessary copies.

3. Explain one meaningful test you added. What behavior does it check, and what implementation error could it catch?

test_document_load_failure checks that attempting to call Document::load() on a non-existent file returns false while leaving all existing document fields (title_, contents_, and sourcePath_) completely unchanged. This catches implementation errors where member variables might clear before successfully opening or reading the target file.

4. Describe one implementation decision that you verified, tested, or revised before submitting your work.

I verified the behavior of Prompt::empty() to ensure it checked strictly whether text_ was empty, rather than checking both title_ and text_. I revised an initial condition check to rely solely on text_.empty(), ensuring compliance with the specification requirements.

5. If generative AI was used, disclose it as required by course policy. If no generative AI was used, state that. The disclosure itself is not used as proof of authorship or understanding.

No generative AI was used.
