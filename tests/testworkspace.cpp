#include <cassert>
#include <iostream>
#include <stdexcept>

#include "Prompt.hpp"
#include "Workspace.hpp"
#include "Document.hpp"
#include "Message.hpp"

void prompt_smoke_test() {
    Prompt p("Reviewer", "Review this requirement.");
    assert(p.title()=="Reviewer");
    assert(!p.empty());
}

void workspace_smoke_test() {
    Workspace w("Demo");
    w.addPrompt(Prompt("Reviewer", "Review this requirement."));
    assert(w.promptCount()== 1);
}

void test_document_load_failure() {
    Document doc("Title", "Contents");
    bool success = doc.load("nonexistent_file.txt");
    
    assert(!success);
    assert(doc.title()=="Title");
    assert(doc.sourcePath().empty());
    assert(doc.contents()=="Contents");
}

void test_document_empty_and_count() {
    Document empty_doc;
    assert(empty_doc.empty());
    assert(empty_doc.characterCount()==0);

    Document filled_doc("Title", "Contents");
    assert(!filled_doc.empty());
    assert(filled_doc.characterCount()== 8);
}

void test_prompt_empty(){
    Prompt title_only("Title","");
    assert(title_only.empty());

    Prompt text_only("", "Text");
    assert(!text_only.empty());
}

void test_message_default_and_equality(){
    Message default_msg;
    assert(default_msg.role() == MessageRole::User);
    assert(default_msg.empty());

    Message m1(MessageRole::Assistant, "Hello");
    Message m2(MessageRole::Assistant, "Hello");
    Message m3(MessageRole::User, "Hello");

    assert(m1==m2);
    assert(m1!=m3);
}

void test_workspace_outofbounds(){
    Workspace w("Test Workspace");

    bool caught_doc=false;
    try{
        w.documentAt(0);
    } catch (const std::out_of_range&) {
        caught_doc= true;
    }
    assert(caught_doc);

    bool caught_prompt=false;
    try{
        w.promptAt(5);
    } catch (const std::out_of_range&) {
        caught_prompt=true;
    }
}

void test_workspace_value_semantics(){
    Workspace w1("Workspace 1");
    w1.addDocument(Document("Doc1", "Content1"));

    Workspace w2 = w1;// copy constructor
    w2.setName("Copied ws");
    w2.documentAt(0).setTitle("Modified Title");

    assert(w1.name()=="Workspace 1");
    assert(w1.documentAt(0).title() == "Doc1");

    assert(w2.name() =="Copied ws");
    assert(w2.documentAt(0).title() == "Modified Title");
}

int main() {
    prompt_smoke_test();
    workspace_smoke_test();

    test_document_load_failure();
    test_document_empty_and_count();
    test_prompt_empty();
    test_message_default_and_equality();
    test_workspace_outofbounds();
    test_workspace_value_semantics();

    // TODO: Add your own meaningful M0 tests.
    // See the Testing Requirements section of the specification.

    std::cout << "M0 tests passed\n";
    return 0;
}
