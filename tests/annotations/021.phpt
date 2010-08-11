--TEST--
Complex Annotations in class test
--FILE--

<?php

[Entity(tableName="users")]
class User
{
    [Column(type="integer")]
    [Id]
    [GeneratedValue(strategy="AUTO")]
    protected $id;

    [ManyToMany(targetEntity="Phonenumber")]
    [JoinTable(
        name="users_phonenumbers",
        joinColumns={
            [JoinColumn(name="user_id", referencedColumnName="id")]
        },
        inverseJoinColumns={
            [JoinColumn(name="phonenumber_id", referencedColumnName="id", unique=true)]
        }
    )]
    function foo() {}
}

$user = new User();

echo 'OK!';

?>
--EXPECT--
OK!